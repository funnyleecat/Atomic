#pragma once

#include <map>
#include <DBMgr.hpp>
#include <Statement.h>
#include <DBExpection.h>
#include <DBIterator.h>
#include "AtomicApi.h"

#ifdef WIN32
#pragma comment( lib, "jsoncpp.lib" )
#endif

namespace ATOMICTEST
{
    //CAtomicApi测试类
    class CAtomicApiTest
    {
    public:
        CAtomicApiTest(const std::string& strAtomicConfDir, const std::string& strDBUtilsConfFile);
        ~CAtomicApiTest();

        //初始化DBUtils，无异常抛出。
        bool InitDBUtils();

        //参数为Test开头的成员函数地址（如：&CAtomicApiTest::TestExample），无异常抛出。
        void Function(void (CAtomicApiTest::* pfnTestFunc)());

        //-------以下测试函数，失败时抛DBUtils::CDBExpection或std::exception异常
    public:
        //测试函数实例
        void TestExample();

        //初始化接口测试
        void TestInit();

        //执行接口(写操作)测试
        void TestExecuteSQL();

        //执行接口(读操作-有出入参)测试
        void TestExecuteQuery();

        //执行接口(读操作-无出入参)测试
        void TestExecuteQuery2();

        //获取SQL信息-数据库执行后的，实际执行的SQL信息
        void TestGetSQLInfo1();

        //获取SQL信息-实际执行的SQL信息
        void TestGetSQLInfo2();

        //获取SQL信息-XML配置的SQL信息
        void TestGetSQLInfo3();

    private:
        std::string m_strAtomicConfDir;
        std::string m_strDBUtilsConfFile;
        ATOMIC::CAtomicApi* m_pCAtomicApi;

        enum PRINT_CHOSE{ PRINT_ALL, PRINT_CMD, PRINT_FILE };
        void PrintHeader(DBUtils::CDBIterator *iter, const std::string& filepath, PRINT_CHOSE print_chose = PRINT_ALL);
        void PrintValues(DBUtils::CDBIterator *iter, const std::string& filepath, unsigned int columnCount, PRINT_CHOSE print_chose = PRINT_ALL);
        void PrintDBIterator(DBUtils::CDBIterator *iter, PRINT_CHOSE print_chose = PRINT_ALL);
        void PrintSQLInfoPtr(const ATOMIC::CSQLInfoPtr& sqlInfoPtr);
    };
}
