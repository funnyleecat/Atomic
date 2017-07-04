#include "AtomicApi.h"
#include "Atomic.h"

#include <workexception.hpp>

namespace ATOMIC
{
    CAtomicApi::CAtomicApi()
    {
    }

    CAtomicApi::~CAtomicApi()
    {
    }

    CAtomicApi* CAtomicApi::CreateObjPtr()
    {
        CAtomic* pCAtomic = new(std::nothrow) CAtomic();
        if (NULL == pCAtomic)
        {
            throw Utils::CWorkException("Failed to create CAtomicApi object");
        }
        return  pCAtomic;
    }
    
    void CAtomicApi::DestroyObjPtr(CAtomicApi*& pCAtomicApi)
    {
        if (pCAtomicApi)
        {
            delete pCAtomicApi;
        }
        pCAtomicApi = NULL;
    } 
}
