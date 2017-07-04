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
    
    

    //参数列表map，Key: CSQLInfo::Arg.pName
    typedef std::map<std::string, CSQLInfo::Arg> ArgMap;
    //参数列表vector
    typedef std::vector<CSQLInfo::Arg> ArgVec;

    class CSQLInfoImpl : public CSQLInfo{
        //GetSQLInfo需要使用
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
