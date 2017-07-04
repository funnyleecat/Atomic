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
    //CAtomicApi������
    class CAtomicApiTest
    {
    public:
        CAtomicApiTest(const std::string& strAtomicConfDir, const std::string& strDBUtilsConfFile);
        ~CAtomicApiTest();

        //��ʼ��DBUtils�����쳣�׳���
        bool InitDBUtils();

        //����ΪTest��ͷ�ĳ�Ա������ַ���磺&CAtomicApiTest::TestExample�������쳣�׳���
        void Function(void (CAtomicApiTest::* pfnTestFunc)());

        //-------���²��Ժ�����ʧ��ʱ��DBUtils::CDBExpection��std::exception�쳣
    public:
        //���Ժ���ʵ��
        void TestExample();

        //��ʼ���ӿڲ���
        void TestInit();

        //ִ�нӿ�(д����)����
        void TestExecuteSQL();

        //ִ�нӿ�(������-�г����)����
        void TestExecuteQuery();

        //ִ�нӿ�(������-�޳����)����
        void TestExecuteQuery2();

        //��ȡSQL��Ϣ-���ݿ�ִ�к�ģ�ʵ��ִ�е�SQL��Ϣ
        void TestGetSQLInfo1();

        //��ȡSQL��Ϣ-ʵ��ִ�е�SQL��Ϣ
        void TestGetSQLInfo2();

        //��ȡSQL��Ϣ-XML���õ�SQL��Ϣ
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
