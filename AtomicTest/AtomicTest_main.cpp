#include <string.h>
#include <iostream>
#include "AtomicTest.h"

#include <workexception.hpp>

int main(int argc, char* argv[])
{

    static const char SCRIPT_CONF_SQL_FLAG[] = "SQL";
    static const char SCRIPT_CONF_STATMENT_INDEX[] = "index";
    int nIndex = 1;
    //TODO: ”–Œ Ã‚
    //Utils::CWorkException cw("%s Attribute[%s] value[%d] existed", SCRIPT_CONF_SQL_FLAG, SCRIPT_CONF_STATMENT_INDEX, nIndex);
    std::string strAtomicConfDir =  
#ifdef WIN32
        "../bin";
#else
        ".";
#endif
    std::string strDBUtilsConfFile =
#ifdef WIN32
        "../bin/AtomicTest.DBUtils.xml";
#else
        "./AtomicTest.DBUtils.xml";
#endif
    
    ATOMICTEST::CAtomicApiTest atomicApiTest(strAtomicConfDir, strDBUtilsConfFile);
    if (atomicApiTest.InitDBUtils())
    {
        atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestExample);
        atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestInit);

        //atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestExecuteSQL);
        //atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestExecuteQuery);
        //atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestExecuteQuery2);
        atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestGetSQLInfo1);
        atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestGetSQLInfo2);
        atomicApiTest.Function(&ATOMICTEST::CAtomicApiTest::TestGetSQLInfo3);
    }
#ifdef WIN32
    system("pause");
#endif // WIN32
    return 0;
}