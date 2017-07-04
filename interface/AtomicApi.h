#pragma once

/***********************************************************************
ģ����        : ATOMIC
�ļ���        : AtomicApi.h
����          : LDG
��������      : 2017/05/15
��ע          : �������ݿ��SQL���ԭ�Ӳ�����ӿڡ�
-----------------------------------------------------------------------
�޸ļ�¼ :
�� ��        �汾     �޸���            �޸�����
2017/05/15   1.0.0    ��¹�            ����
2017/05/17   2.0.0    ��¹�            �ع�
2017/06/08   2.1.0    ��¹�            ����CArgIter
2017/06/08   2.1.1    ��¹�            �ӿ�Execute����
2017/06/20   2.2.0    ��¹�            CArgIter��ΪCSQLInfo������GetSQLInfo�ӿ�
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

//���ݿ����ֿռ�
namespace DBUtils
{
    //���ݿ�������
    class CDBStatement;
}

//ԭ�Ӳ������ֿռ�
namespace ATOMIC
{
 
    /*
    *SQL��Ϣ����
    */
    class ATOMIC_API CSQLInfo
    {
    public:
        //�����ṹ
        struct Arg
        {
            const char* pName;                   //��������-����Ϊ�պ�NULL
            DBUtils::DataType eType;             //��������
            DBUtils::BindDirecation eDirectoion; //��������
            Json::Value jValue;                  //����ȡֵ-�β�ʱΪĬ��ֵ��ʵ��ʱΪʵ��ֵ
            Arg();                               //����Ĭ��-Ĭ��ֵΪ��Чֵ
            operator bool();                     //����ת��-��ֻҪpName/eType/eDirectoion�зǷ�ʱΪfalse������Ϊtrue
        };

    public:
        virtual ~CSQLInfo(){}
        //��ȡSQL��䣨����index˳��ƴ�Ӻ����䣩
        virtual const char* GetSQLText() const = 0;
        //��ȡ����������ͨ��������nameȥ��(���һ����Ч)��Ĳ���������
        virtual unsigned int GetArgCount() const = 0;
        //��ȡ������Ϣ��uIndex��0��ʼ
        virtual const Arg& GetArgInfo(unsigned int uIndex) const = 0;
    };

    //SQL��Ϣ����ָ��
    typedef boost::shared_ptr<CSQLInfo> CSQLInfoPtr;

    /*
    * ���ݿ�ԭ�Ӳ�������ӿ�
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
        *����һ��ԭ�Ӳ����ӿڶ���
        */
        static CAtomicApi* CreateObjPtr();

        /*
        *����һ��ԭ�Ӳ����ӿڶ���
        */
        static void DestroyObjPtr(CAtomicApi*& pCAtomicApi);

    public:
        /*
        *SQL�ű���ʼ������ȡָ��Ŀ¼�µ�xml�ļ�����
        * ��Σ�pSQLXmlDir-SQL�ű�Ŀ¼����Ŀ¼�´������Ҫ���ص�xml�ļ�
        * ���أ�void���������׳�Utils::CWorkException�쳣
        * ˵����ʹ��ǰ����ִ�д˳�ʼ������
        */
        virtual void Initialize(const char* pSQLXmlDir) = 0;

        /*
        *����ԭ�Ӳ���ID��������Σ�ִ�����ݿ����
        *  ��Σ�pCDBStatement-���ݿ��������ָ�룬Ϊ��ʱ������SQLʵ����Ϣ
        *  ��Σ�nAtomicId-ԭ�Ӳ���ID��ȡֵ����xml��ATOMIC-SQL��ǩ��IDȡֵ
        *  ��Σ�jValue-SQLԭ�Ӳ���Json��Σ�Ĭ��Ϊ�գ������Բ�������
        *  ��Σ�lTimeout-������ʱʱ��(����)��Ĭ��ֵ��DBUtils::CDBMgr::Execute�ӿڵ�һ��
        *  ���أ�SQLInfoPtr-SQLʵ�Σ���ֵ�Ǹ�����μ������߼����أ����Կ��ܺ����ò�һ��
        * ˵��1�����ν��������������pCDBStatement��ȡ
        * ˵��2���������׳�Utils::CWorkException�쳣����DBUtils::CDBExpection�쳣
        */
        virtual CSQLInfoPtr Execute(DBUtils::CDBStatement* pCDBStatement, unsigned int nAtomicId, const Json::Value& jValue = Json::Value(), long lTimeout = 3) const = 0;

        /*
        *����ԭ��ID����ȡ����SQL��Ϣ
        * ��Σ�nAtomicId-ԭ�Ӳ���ID��ȡֵ����xml��ATOMIC-SQL��ǩ��IDȡֵ
        * ���أ�SQLInfoPtr��XML���õ�SQL��Ϣ
        * ˵�������ص�SQL��ϢΪ�β���Ϣ
        */
        virtual CSQLInfoPtr GetSQLInfo(unsigned int nAtomicId) const = 0;      
    };

}

