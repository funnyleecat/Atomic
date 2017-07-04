#include <iostream>
#include "AtomicTest.h"
#include "myPrint.hpp"

namespace ATOMICTEST
{
    //对DBUtils::CDBStatement的包装，自己释放与申请
    class CDBStatement
    {
    public:
        CDBStatement(DBUtils::EXEMode exeMode) throw()
        {
            //AllocStatement不会抛异常
            m_pCDBStatement = DBUtils::CDBMgr::Instance().AllocStatement("AtomicTestDB", exeMode);
        }
        ~CDBStatement() throw()
        {
            if (m_pCDBStatement)
            {
                DBUtils::CDBMgr::Instance().Release(m_pCDBStatement);
            }
            m_pCDBStatement = NULL;
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
        DBUtils::CDBStatement* m_pCDBStatement;
        void Check()
        {
            if (!m_pCDBStatement)
            {
                throw std::exception("NULL pCDBStatement");
            }
            return;
        }
    };

    CAtomicApiTest::CAtomicApiTest(const std::string& strAtomicConfDir, const std::string& strDBUtilsConfFile)
        :m_pCAtomicApi(NULL),
        m_strDBUtilsConfFile(strDBUtilsConfFile), m_strAtomicConfDir(strAtomicConfDir)
    {
    }
    CAtomicApiTest::~CAtomicApiTest()
    {
        if (m_pCAtomicApi)
        {
            ATOMIC::CAtomicApi::DestroyObjPtr(m_pCAtomicApi);
        }
        m_pCAtomicApi = NULL;
    }

    bool CAtomicApiTest::InitDBUtils()
    {
        do
        {
            try
            {
                if (DBUtils::CDBMgr::Instance().Init(m_strDBUtilsConfFile))
                {
                    CC::Print::ToTerminal("DBUtils INIT SUCESS");
                    return true;
                }
                CC::Print::ToTerminal("DBUtils INIT FAILED");
            }
            catch (DBUtils::CDBExpection* e)
            {
                CC::Print::ToTerminal(true, 100 + (unsigned int)strlen(e->GetErrorName()), "Catch DBUtils::CDBExpection[%d]: %s", e->GetErrorCode(), e->GetErrorName());
            }
            catch (std::exception& e)
            {
                CC::Print::ToTerminal(true, 100 + (unsigned int)strlen(e.what()), "Catch std::exception: %s", e.what());
            }
            catch (...)
            {
                CC::Print::ToTerminal("Catch an unknow exception");
            }
        } while (0);
        return false;
    }
    void CAtomicApiTest::Function(void (CAtomicApiTest::* pfnTestFunc)())
    {
        CC::Print::ToTerminal("\n\n************* Test Begin *************\n");
        do
        {
            try
            {
                (this->*(pfnTestFunc))();
            }
            catch (DBUtils::CDBExpection* e)
            {
                CC::Print::ToTerminal(true, 100 + (unsigned int)strlen(e->GetErrorName()), "Catch DBUtils::CDBExpection[%d]: %s", e->GetErrorCode(), e->GetErrorName());
            }
            catch (std::exception& e)
            {
                CC::Print::ToTerminal(true, 100 + (unsigned int)strlen(e.what()), "Catch std::exception: %s", e.what());
            }
            catch (...)
            {
                CC::Print::ToTerminal("Catch an unknow exception");
            }
        } while (0);
        CC::Print::ToTerminal("\n************* Test ended *************\n\n");
    }

    void CAtomicApiTest::PrintHeader(DBUtils::CDBIterator *iter, const std::string& filepath, PRINT_CHOSE print_chose)
    {
        if (!iter)
        {
            return;
        }

        bool bFirst = true;
        unsigned int columnCount = iter->GetColumnCount();
        for (unsigned int index = 1; index <= columnCount; ++index)
        {
            DBUtils::ColumnInfo ci = iter->GetColumnInfo(index);
            switch (print_chose)
            {
            case PRINT_CMD:
                CC::Print::ToTerminal(ci.colName, false);
                CC::Print::ToTerminal(" | ", false);
                break;
            case PRINT_FILE:
                CC::Print::ToFile(filepath, ci.colName, false, !bFirst);
                bFirst = false;
                CC::Print::ToFile(filepath, ",", false);
                break;
            default:
                CC::Print::ToTerminal(ci.colName, false);
                CC::Print::ToTerminal(" | ", false);
                CC::Print::ToFile(filepath, ci.colName, false, !bFirst);
                bFirst = false;
                CC::Print::ToFile(filepath, ",", false);
                break;
            }
        }
        switch (print_chose)
        {
        case PRINT_CMD:
            CC::Print::ToTerminal("", true);
            break;
        case PRINT_FILE:
            CC::Print::ToFile(filepath, "", true);
            break;
        default:
            CC::Print::ToTerminal("", true);
            CC::Print::ToFile(filepath, "", true);
            break;
        }

        return;
    }
    void CAtomicApiTest::PrintValues(DBUtils::CDBIterator *iter, const std::string& filepath, unsigned int columnCount, PRINT_CHOSE print_chose)
    {
        if (!iter)
        {
            return;
        }
        bool bRet = false;

        for (unsigned int index = 1; index <= columnCount; ++index)
        {
            const char *p = iter->At(index);
            switch (print_chose)
            {
            case PRINT_CMD:
                CC::Print::ToTerminal(p, false);
                CC::Print::ToTerminal(" | ", false);
                break;
            case PRINT_FILE:
                CC::Print::ToFile(filepath, p, false);
                CC::Print::ToFile(filepath, ",", false);
                break;
            default:
                CC::Print::ToTerminal(p, false);
                CC::Print::ToTerminal(" | ", false);
                CC::Print::ToFile(filepath, p, false);
                CC::Print::ToFile(filepath, ",", false);
                break;
            }
        }
        switch (print_chose)
        {
        case PRINT_CMD:
            CC::Print::ToTerminal("", true);
            break;
        case PRINT_FILE:
            CC::Print::ToFile(filepath, "", true);
            break;
        default:
            CC::Print::ToTerminal("", true);
            CC::Print::ToFile(filepath, "", true);
            break;
        }
        return;
    }
    void CAtomicApiTest::PrintDBIterator(DBUtils::CDBIterator *iter, PRINT_CHOSE print_chose)
    {
        if (!iter)
        {
            return;
        }
        std::string filePath = "Selectdata.txt";
        PrintHeader(iter, filePath, print_chose);
        unsigned int columnCount = iter->GetColumnCount();
        while (iter->Next())
        {
            PrintValues(iter, filePath, columnCount, print_chose);
        }
        return;
    }
    void CAtomicApiTest::PrintSQLInfoPtr(const ATOMIC::CSQLInfoPtr& sqlInfoPtr)
    {
        const char* pSQL = sqlInfoPtr->GetSQLText();
        CC::Print::ToTerminal(true, 100 + (unsigned int)strlen(pSQL), "Get EXE SQL:\n     %s", pSQL);

        unsigned int uArgCount = sqlInfoPtr->GetArgCount();
        if (0 == uArgCount)
        {
            CC::Print::ToTerminal("Get Args: NULL");
            return;
        }
        CC::Print::ToTerminal(true, 100, "Get Args[%d]: ", uArgCount);
        for (unsigned int uIndex = 0; uIndex < uArgCount; ++uIndex)
        {
            CC::Print::ToTerminal(true, 100, "    ----ARG[%d]:", uIndex);
            const ATOMIC::CSQLInfo::Arg& arg = sqlInfoPtr->GetArgInfo(uIndex);

            CC::Print::ToTerminal(true, 100 + (unsigned int)strlen(arg.pName), "      ARG.NAME: %s", arg.pName);
            CC::Print::ToTerminal("      ARG.TYPE: ", false);
            switch (arg.eType)
            {
            case DBUtils::DT_INT:
                CC::Print::ToTerminal("INT");
                break;
            case DBUtils::DT_DOUBLE:
                CC::Print::ToTerminal("DOUBLE");
                break;
            case DBUtils::DT_String:
                CC::Print::ToTerminal("STRING");
                break;
            case DBUtils::DT_Cursor:
                CC::Print::ToTerminal("CUTSOR");
                break;
            default:
                CC::Print::ToTerminal("UNKNOW");
                break;
            }
            CC::Print::ToTerminal("ARG.DIRECATION: ", false);
            switch (arg.eDirectoion)
            {
            case DBUtils::D_IN:
                CC::Print::ToTerminal("IN");
                break;
            case DBUtils::D_INOUT:
                CC::Print::ToTerminal("INOUT");
                break;
            case DBUtils::D_OUT:
                CC::Print::ToTerminal("OUT");
                break;
                CC::Print::ToTerminal("UNKNOW");
                break;
            }

            CC::Print::ToTerminal("     ARG.VALUE: ", false);
            const Json::Value& jValue = arg.jValue;
            //测试时候入参全部当中string，所以不分类型转换
            CC::Print::ToTerminal(jValue.asString());
            /*switch (argIter->GetType())
            {
            case DBUtils::DT_INT:
            CC::Print::ToTerminal(jValue.asInt());
            break;
            case DBUtils::DT_DOUBLE:
            CC::Print::ToTerminal(jValue.asDouble());
            break;
            case DBUtils::DT_String:
            CC::Print::ToTerminal(jValue.asString());
            break;
            case DBUtils::DT_Cursor:
            CC::Print::ToTerminal(jValue.toStyledString());
            break;
            default:
            CC::Print::ToTerminal(jValue.toStyledString());
            break;
            }*/

        }
        return;
    }

    void CAtomicApiTest::TestExample()
    {
        CC::Print::ToTerminal("This is a test function.");
    }
    void CAtomicApiTest::TestInit()
    {
        m_pCAtomicApi = ATOMIC::CAtomicApi::CreateObjPtr();
        m_pCAtomicApi->Initialize(m_strAtomicConfDir.c_str());
        CC::Print::ToTerminal("Init Atomic Api  SUCCESS");
        return;
    }
    void CAtomicApiTest::TestExecuteSQL()
    {
        unsigned int nAtomicId = 1000;
        CDBStatement DBStatement(DBUtils::W_Mode);
        
        m_pCAtomicApi->Execute(DBStatement, nAtomicId);

        CC::Print::ToTerminal("ExecuteSQL SUCCESS");
        return;
    }
    void CAtomicApiTest::TestExecuteQuery()
    {
        unsigned int nAtomicId = 1001;
        CDBStatement DBStatement(DBUtils::R_Mode);

        Json::Value JValue;
        JValue["IN_USER_ID"] = "100000006";
        JValue["IN_OUT_FLAG_NAME"] = "2";

        m_pCAtomicApi->Execute(DBStatement, nAtomicId, JValue);

        CC::Print::ToTerminal(DBStatement->GetBindOutResult("IN_OUT_FLAG_NAME", DBUtils::DT_String));
        CC::Print::ToTerminal(DBStatement->GetBindOutResult("OUT_PASSWORD", DBUtils::DT_String));
        CC::Print::ToTerminal(DBStatement->GetBindOutResult("OUT_GROUP_ID", DBUtils::DT_INT));
        PrintDBIterator(DBStatement->GetCursorRst("OUT_CURSOR"), PRINT_CMD);
        return;
    }
    void CAtomicApiTest::TestExecuteQuery2()
    {
        unsigned int nAtomicId = 1002;
        CDBStatement DBStatement(DBUtils::R_Mode);

        Json::Value JValue;
        //int类型赋值，不能asString()取值，会跑出std::exception：Type is not convertible to string
        JValue["IN_USER_ID"] = 100000000;
        JValue["IN_FUNC_ID"] = "110020";

        m_pCAtomicApi->Execute(DBStatement, nAtomicId, JValue);

        PrintDBIterator(DBStatement->GetCursorRst(""), PRINT_CMD);
        return;
    }
    void CAtomicApiTest::TestGetSQLInfo1()
    {
        unsigned int nAtomicId = 1001;
        CDBStatement DBStatement(DBUtils::R_Mode);

        Json::Value JValue;
        JValue["IN_USER_ID"] = "100000006";
        JValue["IN_OUT_FLAG_NAME"] = "2";

        ATOMIC::CSQLInfoPtr sqlInfoPtr = m_pCAtomicApi->Execute(DBStatement, nAtomicId, JValue);
        PrintSQLInfoPtr(sqlInfoPtr);

        return;
    }
    void CAtomicApiTest::TestGetSQLInfo2()
    {
        unsigned int nAtomicId = 1001;

        Json::Value JValue;
        JValue["IN_USER_ID"] = "100000006";
        //JValue["IN_OUT_FLAG_NAME"] = "2";

        ATOMIC::CSQLInfoPtr sqlInfoPtr = m_pCAtomicApi->Execute(NULL, nAtomicId, JValue);
        PrintSQLInfoPtr(sqlInfoPtr);

        return;
    }

    void CAtomicApiTest::TestGetSQLInfo3()
    {
        unsigned int nAtomicId = 1001;

        ATOMIC::CSQLInfoPtr sqlInfoPtr = m_pCAtomicApi->GetSQLInfo(nAtomicId);
        PrintSQLInfoPtr(sqlInfoPtr);

        return;
    }

}
