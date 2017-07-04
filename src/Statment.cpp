#include "Statment.h"
#include "ConfDef.hpp"

#include <workexception.hpp>

namespace ATOMIC
{
    CStatment::CStatment() :m_strFlag(SCRIPT_CONF_STATMENT)
    {
    }

    CStatment::~CStatment()
    {
    }

    unsigned int CStatment::Init(TiXmlElement *pXmlStatment)
    {
        unsigned int nIndex = GetIndex(pXmlStatment);
        if (GetSQL(pXmlStatment))
        {
            throw Utils::CWorkException("%s[%d] Text value is empty", m_strFlag.c_str(), nIndex);
        }
        return nIndex;
    }

    bool CStatment::GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const
    {
        strSQL = m_strSQL;
        return false;
    }

    bool CStatment::GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg,const Json::Value& jsonActual) const
    {
        strSQL = m_strSQL;
        //不使用参数
        return false;
    }
       
    unsigned int CStatment::GetIndex(TiXmlElement* pXmlStatment)
    {
        int nIndex = 0;
        if (NULL == pXmlStatment || TIXML_SUCCESS != pXmlStatment->QueryIntAttribute(SCRIPT_CONF_STATMENT_INDEX, &nIndex))
        {
            throw Utils::CWorkException("Attribute TAG[%s] not found", SCRIPT_CONF_STATMENT_INDEX);
        }
        if (nIndex < 1)
        {
            throw Utils::CWorkException("Attribute[%s] value[%d] must be a positive integer", SCRIPT_CONF_STATMENT_INDEX, nIndex);
        }
        return nIndex;
    }
    
    bool CStatment::GetSQL(TiXmlElement* pXmlStatment)
    {
        m_strSQL.clear();
        const char* pSQLText = pXmlStatment->GetText();
        if (NULL != pSQLText)
        {
            m_strSQL = pSQLText;
        }
        return m_strSQL.empty();
    }
 
}
