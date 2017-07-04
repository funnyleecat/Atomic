#pragma once

#include "AtomicApi.h"
#include "SQL.h"

namespace ATOMIC
{
    //根配置标签，对应SCRIPT_CONF_FLAG标签
    class CAtomic : public CAtomicApi
    {
    public:
        virtual void Initialize(const char* pSQLXmlDir);
        virtual CSQLInfoPtr Execute(DBUtils::CDBStatement* pCDBStatement, unsigned int nAtomicId, const Json::Value& jValue, long lTimeout) const;
        virtual CSQLInfoPtr GetSQLInfo(unsigned int nAtomicId) const;
    private:        
        //SQL对象MAP
        CSQLMap m_CSQLMap; 

        //获取xml文件列表，为空也会抛出异常
        void GetXmlFiles(const char* strXMLDir, std::vector<std::string>& vecXmlPath) const;

        //根据一个配置初始化对象
        void Init(TiXmlElement* pXmlAtomic);

        CSQLInfoPtr GetSQLInfo(const std::string& strSQL, const ArgMap& argMap) const;

    };
}