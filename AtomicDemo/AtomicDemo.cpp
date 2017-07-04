#include "AtomicDemo.hpp"
#include "DBUtilsDemo.hpp"

#include <iostream>

static void AtomicAndDBUtilsTest(const std::string& strDBUtilsConfFile, const std::string& strAtomicSQLDir)
{
    std::cout << "Begin Test Atomic and DBUtils..." << endl;
    try
    {
        //throw Utils::CWorkException("code[%d]-%s", 222, "测试log");
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
#ifdef WIN32
    std::string strDBUtilsConfFile = "../bin/AtomicTest.DBUtils.xml";
    std::string strAtomicSQLDir = "../bin";
#else
    /*
    注意1：make完成之后一定要 make copy！
    注意2：DBUtils需要添加环境变量！！！
    export NLS_LANG = "SIMPLIFIED CHINESE_CHINA.ZHS16GBK"
    export OCI_PATH = "./"
    注意3：输出结果乱码？不要慌张，由于NLS_LANG为GBK的，linux终端编码为utf8
    所以解决办法1：NLS_LANG的值设置为SIMPLIFIED CHINESE_CHINA.UTF8；解决办法2：将输出结果>>到文件中
    当然，这两个办法还是需要DBUtils修复环境变量值的判断，
    即DT_DB_NLS_LANG_NAME取值不应写死为DT_DB_NLS_LANG_VALUE，其值只有NLS_LANG的上述2种之一即可
    */
    std::string strDBUtilsConfFile = "./AtomicTest.DBUtils.xml";
    std::string strAtomicSQLDir = "./";
#endif

    AtomicAndDBUtilsTest(strDBUtilsConfFile, strAtomicSQLDir);

#ifdef WIN32
    system("pause");
#endif // WIN32
    return 0;
}



