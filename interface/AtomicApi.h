#pragma once

/***********************************************************************
模块名        : ATOMIC
文件名        : AtomicApi.h
作者          : LDG
创建日期      : 2017/05/15
备注          : 定义数据库的SQL语句原子操作层接口。
-----------------------------------------------------------------------
修改记录 :
日 期        版本     修改人            修改内容
2017/05/15   1.0.0    黎德国            创建
2017/05/17   2.0.0    黎德国            重构
2017/06/08   2.1.0    黎德国            新增CArgIter
2017/06/08   2.1.1    黎德国            接口Execute返回
2017/06/20   2.2.0    黎德国            CArgIter改为CSQLInfo，新增GetSQLInfo接口
**************************************************************************/

#ifdef WIN32
#   ifdef ATOMIC_EXPORTS
#       define ATOMIC_API __declspec(dllexport)
#   else
#       define ATOMIC_API __declspec(dllimport)
#   endif
#else
#   define ATOMIC_API
#endif //WIN32

#include <json/json.h>
#include <boost/shared_ptr.hpp>
#include <exportDef.hpp>

//数据库名字空间
namespace DBUtils
{
    //数据库名对象
    class CDBStatement;
}

//原子操作名字空间
namespace ATOMIC
{
 
    /*
    *SQL信息对象
    */
    class ATOMIC_API CSQLInfo
    {
    public:
        //参数结构
        struct Arg
        {
            const char* pName;                   //参数名称-不能为空和NULL
            DBUtils::DataType eType;             //参数类型
            DBUtils::BindDirecation eDirectoion; //参数类型
            Json::Value jValue;                  //参数取值-形参时为默认值，实参时为实际值
            Arg();                               //构造默认-默认值为无效值
            operator bool();                     //类型转换-即只要pName/eType/eDirectoion有非法时为false，否则为true
        };

    public:
        virtual ~CSQLInfo(){}
        //获取SQL语句（按照index顺序拼接后的语句）
        virtual const char* GetSQLText() const = 0;
        //获取参数数量（通过参数名name去重(最后一个有效)后的参数个数）
        virtual unsigned int GetArgCount() const = 0;
        //获取参数信息，uIndex从0开始
        virtual const Arg& GetArgInfo(unsigned int uIndex) const = 0;
    };

    //SQL信息对象指针
    typedef boost::shared_ptr<CSQLInfo> CSQLInfoPtr;

    /*
    * 数据库原子操作对象接口
    */
    class ATOMIC_API CAtomicApi
    {
    protected:
        CAtomicApi();
        CAtomicApi(const CAtomicApi&);
        CAtomicApi &operator=(const CAtomicApi&);
    public:
        virtual ~CAtomicApi();

        /*
        *创建一个原子操作接口对象
        */
        static CAtomicApi* CreateObjPtr();

        /*
        *销毁一个原子操作接口对象
        */
        static void DestroyObjPtr(CAtomicApi*& pCAtomicApi);

    public:
        /*
        *SQL脚本初始化，读取指定目录下的xml文件配置
        * 入参：pSQLXmlDir-SQL脚本目录，该目录下存放着需要加载的xml文件
        * 返回：void，出错则抛出Utils::CWorkException异常
        * 说明：使用前必须执行此初始化操作
        */
        virtual void Initialize(const char* pSQLXmlDir) = 0;

        /*
        *根据原子操作ID及参数入参，执行数据库操作
        *  入参：pCDBStatement-数据库操作对象指针，为空时仅返回SQL实参信息
        *  入参：nAtomicId-原子操作ID，取值来着xml的ATOMIC-SQL标签的ID取值
        *  入参：jValue-SQL原子操作Json入参，默认为空，即可以不传参数
        *  入参：lTimeout-操作超时时间(分钟)，默认值和DBUtils::CDBMgr::Execute接口的一致
        *  返回：SQLInfoPtr-SQL实参，该值是根据入参及配置逻辑返回，所以可能和配置不一样
        * 说明1：出参结果及结果集，需从pCDBStatement获取
        * 说明2：出错则抛出Utils::CWorkException异常，或DBUtils::CDBExpection异常
        */
        virtual CSQLInfoPtr Execute(DBUtils::CDBStatement* pCDBStatement, unsigned int nAtomicId, const Json::Value& jValue = Json::Value(), long lTimeout = 3) const = 0;

        /*
        *根据原子ID，获取配置SQL信息
        * 入参：nAtomicId-原子操作ID，取值来着xml的ATOMIC-SQL标签的ID取值
        * 返回：SQLInfoPtr，XML配置的SQL信息
        * 说明：返回的SQL信息为形参信息
        */
        virtual CSQLInfoPtr GetSQLInfo(unsigned int nAtomicId) const = 0;      
    };

}

