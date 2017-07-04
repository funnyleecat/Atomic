#pragma once

/*DBUtils使用简单demo
好吧，本来不属于AtomicDemo的范畴，但为方便使用，还是封装一个
相关配置参见AtomicDemo.hpp的说明
其他查询需要对DBUtils使用的，也可以直接使用这个即可
*/

#include <string>

#include <DBExpection.h>
#include <ExportDef.hpp>
#include <DBMgr.hpp>
#include <Statement.h>

namespace DEMO_DBUTILS
{
    /*对DBUtils的封装，好吧，准确的说应该是对DBUtils::CDBStatement的封装
    由于该对象需要申请与释放，麻烦，遇到异常的话更不好处理
    所以，封装最主要的目的就是这里啦
    */
    class CStatement
    {
        CStatement(const CStatement&);
        CStatement& operator=(const CStatement&);
    public:
        CStatement(DBUtils::EXEMode exeMode) throw()
        {
            //AllocStatement不会抛异常
            m_pCDBStatement = DBUtils::CDBMgr::Instance().AllocStatement(CONF_DBUTILS_UNIQUEID, exeMode);
        }
        virtual ~CStatement()
        {
            if (m_pCDBStatement)
            {
                DBUtils::CDBMgr::Instance().Release(m_pCDBStatement);
            }
            m_pCDBStatement = NULL;
        }

    public:
        //初始化，必须在程序开始处初始化
        static void Initialize(const std::string& strDBUtilsConfFile)
        {
            DBUtils::CDBMgr::Instance().Init(strDBUtilsConfFile);
        }

        operator DBUtils::CDBStatement* ()
        {
            Check();
            return m_pCDBStatement;
        }
        DBUtils::CDBStatement* operator->()
        {
            Check();
            return m_pCDBStatement;
        }

    private:
        //对应DBUtils配置DBGV/DBLogicNode/UniqueId的取值
        static std::string CONF_DBUTILS_UNIQUEID;
        DBUtils::CDBStatement* m_pCDBStatement;
        void Check()
        {
            if (!m_pCDBStatement)
            {
                throw Utils::CWorkException("NULL DBUtils::CDBStatement Object");
            }
            return;
        }
    };

    std::string CStatement::CONF_DBUTILS_UNIQUEID = "AtomicTestDB";
}

