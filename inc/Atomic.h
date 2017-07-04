#pragma once

#include "AtomicApi.h"
#include "SQL.h"

namespace ATOMIC
{
    //�����ñ�ǩ����ӦSCRIPT_CONF_FLAG��ǩ
    class CAtomic : public CAtomicApi
    {
    public:
        virtual void Initialize(const char* pSQLXmlDir);
        virtual CSQLInfoPtr Execute(DBUtils::CDBStatement* pCDBStatement, unsigned int nAtomicId, const Json::Value& jValue, long lTimeout) const;
        virtual CSQLInfoPtr GetSQLInfo(unsigned int nAtomicId) const;
    private:        
        //SQL����MAP
        CSQLMap m_CSQLMap; 

        //��ȡxml�ļ��б�Ϊ��Ҳ���׳��쳣
        void GetXmlFiles(const char* strXMLDir, std::vector<std::string>& vecXmlPath) const;

        //����һ�����ó�ʼ������
        void Init(TiXmlElement* pXmlAtomic);

        CSQLInfoPtr GetSQLInfo(const std::string& strSQL, const ArgMap& argMap) const;

    };
}