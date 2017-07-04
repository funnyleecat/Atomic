#include "Atomic.h"
#include "SQLInfo.h"
#include "ConfDef.hpp"

#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>

#include <StringFunc.hpp>
#include <workexception.hpp>

#include <Statement.h>

namespace ATOMIC
{
    
    void CAtomic::Initialize(const char* pSQLXmlDir)
    {
        m_CSQLMap.clear();
        std::vector<std::string> vecXmlPath;
        GetXmlFiles(pSQLXmlDir, vecXmlPath);
        try
        {
            for (std::vector<std::string>::size_type xmlIndex = 0; xmlIndex < vecXmlPath.size(); xmlIndex++)
            {
                TiXmlDocument XmlDoc(vecXmlPath[xmlIndex].c_str());
                if (!XmlDoc.LoadFile())
                {
                    throw Utils::CWorkException("Failed load: %s!", vecXmlPath[xmlIndex].c_str());
                }
                Init(XmlDoc.RootElement());
            }
        }
        catch (std::exception& e)
        {
            throw Utils::CWorkException("Initialize XML Exception(%s)", e.what());
        }
        return;
    }

    CSQLInfoPtr CAtomic::Execute(DBUtils::CDBStatement* pCDBStatement, unsigned int nAtomicId, const Json::Value& jValue, long lTimeout) const
    { 
        const CSQLMap::const_iterator& it = m_CSQLMap.find(nAtomicId);
        if (m_CSQLMap.end() == it)
        {
            throw Utils::CWorkException("SQL id[%d] not find!", nAtomicId);
        }

        ArgMap argMap;
        std::string strSQL;
        it->second.GetSQLInfo(strSQL, argMap, jValue);

        if (pCDBStatement)
        {
            it->second.Execute(pCDBStatement, strSQL, argMap, lTimeout);
        }

        return GetSQLInfo(strSQL, argMap);
    }

    CSQLInfoPtr CAtomic::GetSQLInfo(unsigned int nAtomicId) const
    {
        const CSQLMap::const_iterator& it = m_CSQLMap.find(nAtomicId);
        if (m_CSQLMap.end() == it)
        {
            throw Utils::CWorkException("SQL id[%d] not find!", nAtomicId);
        }

        std::string strSQL;
        ArgMap argMap;
        it->second.GetSQLInfo(strSQL, argMap);

        return GetSQLInfo(strSQL, argMap);
    }

    void CAtomic::GetXmlFiles(const char* strXMLDir, std::vector<std::string> &vecXmlPath) const
    {
        unsigned int nXMLCount = 0;
        try
        {
            boost::filesystem::path dir(strXMLDir);
            if (!boost::filesystem::is_directory(dir))
            {
                throw Utils::CWorkException("%s is not directory!", strXMLDir);
            }

            boost::filesystem::directory_iterator end;
            for (boost::filesystem::directory_iterator pos(dir); pos != end; pos++)
            {
                if (std::string::npos != pos->path().string().find(".xml"))
                {
                    vecXmlPath.push_back(pos->path().string());
                    ++nXMLCount;
                }
            }
        }
        catch (std::exception& e)
        {
            throw Utils::CWorkException(e.what());
        }
        catch (...)
        {
            throw Utils::CWorkException("Get XML file unknow error!");
        }
        if (nXMLCount < 1)
        {
            throw Utils::CWorkException("SQL XML is empty!");
        }
        return;
    }
    
    void CAtomic::Init(TiXmlElement* pXmlAtomic)
    {
        if (NULL == pXmlAtomic || !StringUtil::Equal(pXmlAtomic->Value(), SCRIPT_CONF_FLAG))
        {
            //throw Utils::CWorkException("TAG[%s] note find", SCRIPT_CONF_FLAG);
            //不是合法的XML文件，直接忽略，不用抛出异常
            return;
        }
        CSQL cSQL;
        unsigned int nId = 0;
        TiXmlElement *pXmlSQL = pXmlAtomic->FirstChildElement();
        for (; pXmlSQL; pXmlSQL = pXmlSQL->NextSiblingElement())
        {
            nId = cSQL.Init(pXmlSQL);
            if (0 == nId)
            {
                continue;
            }
            if (m_CSQLMap.end() != m_CSQLMap.find(nId))
            {
                throw Utils::CWorkException("%s Attribute[%s] value[%d] existed", SCRIPT_CONF_SQL_FLAG, SCRIPT_CONF_SQL_ID, nId);
            }
            m_CSQLMap.insert(std::make_pair(nId, cSQL));
        }
        return;
    }

    CSQLInfoPtr CAtomic::GetSQLInfo(const std::string& strSQL, const ArgMap& argMap) const
    {
        CSQLInfoPtr sqlInfoPtr(new(std::nothrow) CSQLInfoImpl());
        if (sqlInfoPtr)
        {
            CSQLInfoImpl* pCSQLInfoImpl = (CSQLInfoImpl*)sqlInfoPtr.get();
            pCSQLInfoImpl->m_strSQL = strSQL;
            pCSQLInfoImpl->m_argVec.clear();
            for (ArgMap::const_iterator it = argMap.begin(); it != argMap.end(); ++it)
            {
                pCSQLInfoImpl->m_argVec.push_back(it->second);
            }
        }
        return sqlInfoPtr;
    }
}
