#pragma once

/*DBUtilsʹ�ü�demo
�ðɣ�����������AtomicDemo�ķ��룬��Ϊ����ʹ�ã����Ƿ�װһ��
������òμ�AtomicDemo.hpp��˵��
������ѯ��Ҫ��DBUtilsʹ�õģ�Ҳ����ֱ��ʹ���������
*/

#include <string>

#include <DBExpection.h>
#include <ExportDef.hpp>
#include <DBMgr.hpp>
#include <Statement.h>

namespace DEMO_DBUTILS
{
    /*��DBUtils�ķ�װ���ðɣ�׼ȷ��˵Ӧ���Ƕ�DBUtils::CDBStatement�ķ�װ
    ���ڸö�����Ҫ�������ͷţ��鷳�������쳣�Ļ������ô���
    ���ԣ���װ����Ҫ��Ŀ�ľ���������
    */
    class CStatement
    {
        CStatement(const CStatement&);
        CStatement& operator=(const CStatement&);
    public:
        CStatement(DBUtils::EXEMode exeMode) throw()
        {
            //AllocStatement�������쳣
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
        //��ʼ���������ڳ���ʼ����ʼ��
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
        //��ӦDBUtils����DBGV/DBLogicNode/UniqueId��ȡֵ
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

