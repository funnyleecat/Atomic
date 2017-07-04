#pragma once

#include "AtomicApi.h"

#include <vector>
#include <map>
#include <json/json.h>

#if WIN32
#pragma comment( lib, "jsoncpp.lib" )
#endif

namespace ATOMIC
{
    
    

    //�����б�map��Key: CSQLInfo::Arg.pName
    typedef std::map<std::string, CSQLInfo::Arg> ArgMap;
    //�����б�vector
    typedef std::vector<CSQLInfo::Arg> ArgVec;

    class CSQLInfoImpl : public CSQLInfo{
        //GetSQLInfo��Ҫʹ��
        friend class CAtomic;
    public:
        virtual ~CSQLInfoImpl(){}
        virtual const char* GetSQLText() const;
        virtual unsigned int GetArgCount() const;
        virtual const Arg& GetArgInfo(unsigned int uIndex) const;

    private:    
        std::string m_strSQL;
        ArgVec m_argVec;
    };
}
