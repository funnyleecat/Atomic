#include "AtomicDemo.hpp"
#include "DBUtilsDemo.hpp"

#include <iostream>

static void AtomicAndDBUtilsTest(const std::string& strDBUtilsConfFile, const std::string& strAtomicSQLDir)
{
    std::cout << "Begin Test Atomic and DBUtils..." << endl;
    try
    {
        //DBUtils初始化
        DEMO_DBUTILS::CStatement::Initialize(strDBUtilsConfFile);

        //Atomic初始化
        DEMO_ATOMIC::CAtomic g_atomic;
        g_atomic.Initialize(strAtomicSQLDir);

        //准备入参
        DEMO_DBUTILS::CStatement pDBStatement(DBUtils::R_Mode);
        unsigned int nAtomicId = DEMO_ATOMIC::CAtomic::ID_1001;
        Json::Value JValue;
        JValue["IN_USER_ID"] = "100000006";
        JValue["IN_OUT_FLAG_NAME"] = "2";

        //执行并接收返回
        ATOMIC::CSQLInfoPtr sqlInfoPtr = g_atomic.Execute(pDBStatement, nAtomicId, JValue);

        //打印执行SQL的语句
        std::cout << std::endl;
        std::cout << "  Get SQL text:\n     " << sqlInfoPtr->GetSQLText() << std::endl;

        //打印执行SQL的参数
        std::cout << std::endl;
        unsigned int uArgCount = sqlInfoPtr->GetArgCount();
        std::cout << "Get Args count: " << uArgCount << std::endl;
        for (unsigned int uIndex = 0; uIndex < uArgCount; ++uIndex)
        {
            std::cout << "    ----ARG[" << uIndex << "]:" << std::endl;
            const ATOMIC::CSQLInfo::Arg& arg = sqlInfoPtr->GetArgInfo(uIndex);
            std::cout << "      ARG.NAME: " << arg.pName << std::endl;
            std::cout << "      ARG.TYPE: " << arg.eType << std::endl;
            std::cout << "ARG.DIRECATION: " << arg.eDirectoion << std::endl;
            std::cout << "     ARG.VALUE: " << arg.jValue.asString() << std::endl;
        }

        //获取出参结果
        std::cout << std::endl;
        std::cout << "Get OUT bind IN_OUT_FLAG_NAME: " << pDBStatement->GetBindOutResult("IN_OUT_FLAG_NAME", DBUtils::DT_String) << std::endl;
        std::cout << "Get OUT bind OUT_PASSWORD    : " << pDBStatement->GetBindOutResult("OUT_PASSWORD", DBUtils::DT_String) << std::endl;
        std::cout << "Get OUT bind OUT_GROUP_ID    : " << pDBStatement->GetBindOutResult("OUT_GROUP_ID", DBUtils::DT_String) << std::endl;
        std::cout << "Get OUT bind OUT_CURSOR      : " << pDBStatement->GetBindOutResult("IN_OUT_FLAG_NAME", DBUtils::DT_String) << std::endl;
        DBUtils::CDBIterator* iter = pDBStatement->GetCursorRst("OUT_CURSOR");

        //打印查询结果表头
        std::cout << std::endl;
        unsigned int columnCount = iter->GetColumnCount();
        std::cout << "    result header count: " << columnCount << std::endl;
        for (unsigned int index = 1; index <= columnCount; ++index)
        {
            DBUtils::ColumnInfo ci = iter->GetColumnInfo(index);
            std::cout << ci.colName << "(" << ci.type << "), ";
        }
        std::cout << endl;

        //打印查询结果集
        std::cout << std::endl;
        std::cout << "    result values: " << std::endl;
        unsigned int uRowCount = 0;
        while (iter->Next())
        {
            std::cout << "----row[" << uRowCount << "]: ";
            for (unsigned int uIndex = 1; uIndex <= columnCount; ++uIndex)
            {
                std::cout << iter->At(uIndex) << ", ";
            }
            std::cout << endl;
            uRowCount++;
        }

        //所有的测试都通过啦
        std::cout << std::endl;
        std::cout << "----All Execute Successed." << std::endl;
    }
    catch (DBUtils::CDBExpection* e)
    {
        std::cout << "Catch DBUtils::CDBExpection[" << e->GetErrorCode() << "]: " << e->GetErrorName() << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << "Catch std::exception: " << e.what() << std::endl;
    }
    catch (...)
    {
        std::cout << "Catch an unknow exception" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Ended Test Atomic and DBUtils." << std::endl;
    return;
}

int main(int argc, char* argv[])
{
    AtomicAndDBUtilsTest("../bin/AtomicTest.DBUtils.xml", "../bin");

#ifdef WIN32
    system("pause");
#endif // WIN32
    return 0;
}



