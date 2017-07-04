#pragma once

/*Atomic使用demo
1，本demo把Atomic的接口封装了一下，这样使用的时候就不用考虑内存释放的问题了

2，本demo的运行还需要DBUtils的接口，DBUtils的封装参见DBUtilsDemo.hpp

3，VS需要的配置说明
(1)包含目录：
../../../../lib_libSelf/cross/Atomic/interface;
../../../../lib_libSelf/cross/DBUtils/interface
../../../../lib_libSelf/cross/utils/inc;
../../../../lib/cross/boost/include
../../../../lib/cross/tinyxml/inc;
../../../../lib/cross/log4cpp/inc;
../../../../lib/cross/jsoncpp/inc;
(2)库目录：
../../../../lib_libSelf/cross/Atomic/win32/Debug;
../../../../lib_libSelf/cross/DBUtils/Win32/Debug;
../../../../lib_libSelf/cross/utils/Debug;
../../../../lib/cross/boost/lib/win32;
../../../../lib/cross/tinyxml/x86/DynamicDebug;
../../../../lib/cross/log4cpp/x86/DynamicDebug;
../../../../lib/cross/jsoncpp/x86/StaticDebug;
(3)附加依赖库：
Atomic.lib;DBUtils.lib;utils.lib;tinyxml.lib;log4cpp.lib;jsoncpp.lib
(4)后期生成事件：
copy "..\\..\\..\\..\\lib_libSelf\\cross\\Atomic\\win32\\Debug\\Atomic.dll"     "$(OutDir)\"
copy "..\\..\\..\\..\\lib_libSelf\\cross\\DBUtils\\Win32\\Debug\\DBUtils.dll"     "$(OutDir)\"
copy "..\\..\\..\\..\\lib_libSelf\\cross\\utils\\Debug\\utils.dll"     "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\instantclient_12_1\\win32\\oci.dll"         "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\instantclient_12_1\\win32\\oraons.dll"      "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\instantclient_12_1\\win32\\oraocci12d.dll"  "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\instantclient_12_1\\win32\\oraociei12.dll"  "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\ocilib-4.3.0\\lib\\win32\\DynamicDebug\\ociliba.dll" "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\instantclient_12_1\\win32\\oci.dll"         "$(ProjectDir)\"
copy "..\\..\\..\\..\\lib\\cross\\jsoncpp\\x86\\DynamicDebug\\jsoncpp.dll"             "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\log4cpp\\x86\\DynamicDebug\\log4cpp.dll"             "$(OutDir)\"
copy "..\\..\\..\\..\\lib\\cross\\tinyxml\\x86\\DynamicDebug\\tinyxml.dll"             "$(OutDir)\"
copy "$(SolutionDir)\bin\\MTSCS.conf.xml"        "$(OutDir)\"
copy "$(SolutionDir)\bin\\MTSCS.DBUtils.xml"    "$(OutDir)\"
if not exist "$(OutDir)\MTSCS.Atomic" ( md "$(OutDir)\MTSCS.Atomic")
copy "$(SolutionDir)\bin\\MTSCS.Atomic\\MTSCS.SQL.xml"   "$(OutDir)\MTSCS.Atomic\\"
(5)运行库：多线程调试(/MTD)

4，其他项目如果需要的话，直接拷贝本文件到相应的目录，并做[说明3]的步骤即可

*/


#include <string>

#include <AtomicApi.h>

#include <workexception.hpp>

namespace DEMO_ATOMIC
{
    //对ATOMIC::CAtomicApi的封装，主要目的是不用自己管理CAtomicApi指针对象
    class CAtomic
    {
        ATOMIC::CAtomicApi* m_atomic;

    public:
        //原子ID自己定义，但必须和配置一致
        static unsigned int ID_1001;
        static unsigned int ID_1002;

        CAtomic() : m_atomic(NULL)
        {
        }

        ~CAtomic()throw()
        {
            if (m_atomic)
            {
                ATOMIC::CAtomicApi::DestroyObjPtr(m_atomic);
            }
            m_atomic = NULL;
        }

    public:
        void Initialize(const std::string& strAtomicSQLDir)
        {
            m_atomic = ATOMIC::CAtomicApi::CreateObjPtr();
            if (!m_atomic)
            {
                throw Utils::CWorkException("Failed to ATOMIC::CAtomicApi object");
            }
            m_atomic->Initialize(strAtomicSQLDir.c_str());
        }

        ATOMIC::CSQLInfoPtr Execute(DBUtils::CDBStatement* pCDBStatement, unsigned int nAtomicId, const Json::Value& jValue) const
        {
            if (!m_atomic)
            {
                throw Utils::CWorkException("NULL ATOMIC::CAtomicApi Object");
            }
            return m_atomic->Execute(pCDBStatement, nAtomicId, jValue);
        }

        ATOMIC::CSQLInfoPtr GetSQLInfo(unsigned int nAtomicId) const
        {
            if (!m_atomic)
            {
                throw Utils::CWorkException("NULL ATOMIC::CAtomicApi Object");
            }
            return m_atomic->GetSQLInfo(nAtomicId);
        }
    private:

    };

    unsigned int CAtomic::ID_1001 = 1001;
    unsigned int CAtomic::ID_1002 = 1002;
 
}
