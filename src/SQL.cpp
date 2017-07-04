#include "SQL.h"
#include "Statment.h"
#include "Optional.h"
#include "Required.h"
#include "ConfDef.hpp"

#include <StringFunc.hpp>
#include <workexception.hpp>

#include <DBMgr.hpp>
#include <Statement.h>

namespace ATOMIC
{
    
    unsigned int CSQL::Init(TiXmlElement* pXmlSQL)
    {
        m_CStatmentMap.clear();
        unsigned int nId = 0;
        if (NULL == pXmlSQL || !StringUtil::Equal(pXmlSQL->Value(), SCRIPT_CONF_SQL_FLAG))
        {
            return nId;
        }
        nId = GetId(pXmlSQL);

        unsigned int nIndex = 0;
        TiXmlElement *pXmlStatment = pXmlSQL->FirstChildElement();
        for (; pXmlStatment; pXmlStatment = pXmlStatment->NextSiblingElement())
        {
            CStatmentPtr pCStatmentPtr = GetCStatmentPtr(pXmlStatment);
            if (NULL == pCStatmentPtr)
            {
                continue;
            }
            nIndex = pCStatmentPtr->Init(pXmlStatment);
            if (0 == nIndex)
            {
                continue;
            }
            if (m_CStatmentMap.end() != m_CStatmentMap.find(nIndex))
            {
                throw Utils::CWorkException("%s Attribute[%s] value[%d] existed", SCRIPT_CONF_SQL_FLAG, SCRIPT_CONF_STATMENT_INDEX, nIndex);
            }
            m_CStatmentMap.insert(std::make_pair(nIndex, pCStatmentPtr));
        }
        return nId;
    }

    unsigned int CSQL::GetId(TiXmlElement* pXmlSQL)
    {
        int nId = 0;
        if (TIXML_SUCCESS != pXmlSQL->QueryIntAttribute(SCRIPT_CONF_SQL_ID, &nId))
        {
            throw Utils::CWorkException("%s Attribute TAG[%s] not found", SCRIPT_CONF_SQL_FLAG, SCRIPT_CONF_SQL_ID);
        }
        if (nId < 1)
        {
            throw Utils::CWorkException("%s Attribute[%s] value[%d] must be a positive integer", SCRIPT_CONF_SQL_FLAG, SCRIPT_CONF_SQL_ID, nId);
        }
        return nId;
    }
   
    CSQL::CStatmentPtr CSQL::GetCStatmentPtr(TiXmlElement *pXmlStatment)
    {
        const char* pStatmentFlag = pXmlStatment->Value();
        if (StringUtil::Equal(pStatmentFlag, SCRIPT_CONF_STATMENT))
        {
            return CStatmentPtr(new(std::nothrow) CStatment());
        }
        else if (StringUtil::Equal(pStatmentFlag, SCRIPT_CONF_STATMENT_REQUIRED))
        {
            return CStatmentPtr(new(std::nothrow) CRequired());
        }
        else if (StringUtil::Equal(pStatmentFlag, SCRIPT_CONF_STATMENT_OPTIONAL))
        {
            return CStatmentPtr(new(std::nothrow) COptional());
        }
        return CSQL::CStatmentPtr();
    }
    
    void CSQL::Execute(DBUtils::CDBStatement* pCDBStatement, const std::string& strSQL, const ArgMap& argMap, long lTimeout) const
    {  
        pCDBStatement->BindCmd(strSQL.c_str());

        BindValues(pCDBStatement, argMap);

        DBUtils::CDBMgr& dbMgr = DBUtils::CDBMgr::Instance();
        dbMgr.Execute(pCDBStatement, lTimeout);

        return;
    }
      
    void CSQL::GetSQLInfo(std::string& strSQL, ArgMap& argMap) const
    {
        strSQL.clear();
        argMap.clear();
        static std::string strStatementJoint = " ";
        CSQLInfo::Arg arg;
        std::string strSubSQL;
        for (CStatmentMap::const_iterator it = m_CStatmentMap.begin(); it != m_CStatmentMap.end(); ++it)
        {
            if (it->second->GetSQLInfo(strSubSQL, arg))
            {
                argMap[arg.pName] = arg;
            }
            strSQL += strSubSQL;
            strSQL += strStatementJoint;
        }
        return;
    }

    void CSQL::GetSQLInfo(std::string& strSQL, ArgMap& argMap, const Json::Value& jValue) const
    {
        strSQL.clear();
        argMap.clear();
        static std::string strStatementJoint = " ";
        std::string strSubSQL;
        for (CStatmentMap::const_iterator it = m_CStatmentMap.begin(); it != m_CStatmentMap.end(); ++it)
        {
            CSQLInfo::Arg arg;
            if (it->second->GetSQLInfo(strSubSQL, arg, jValue))
            {
                argMap[arg.pName] = arg;
            }
            strSQL += strSubSQL;
            strSQL += strStatementJoint;
        }
        return;
    }
    
    void CSQL::BindValues(DBUtils::CDBStatement* pCDBStatement, const ArgMap& argMap) const
    {
        for (ArgMap::const_iterator it = argMap.begin(); it != argMap.end(); ++it)
        {
            const CSQLInfo::Arg& arg = it->second;
            switch (arg.eType)
            {
            case DBUtils::DT_String:
                pCDBStatement->BindString(arg.pName, CSQL::ToString(arg.jValue).c_str(), arg.eDirectoion, arg.jValue.isNull());
                break;
            case DBUtils::DT_INT:
                pCDBStatement->BindInt(arg.pName, CSQL::ToInt(arg.jValue), arg.eDirectoion, arg.jValue.isNull());
                break;
            case DBUtils::DT_DOUBLE:
                pCDBStatement->BindDouble(arg.pName, CSQL::ToDouble(arg.jValue), arg.eDirectoion, arg.jValue.isNull());
                break;
            case DBUtils::DT_Cursor:
                pCDBStatement->BindOutCursor(arg.pName);
                break;
            default:
                break;
            }
            //continue;
        }
        return;
    }
    
    bool CSQL::ToBool(const Json::Value& jsonValue, bool bDefault)
    {
        //不用try catch是因为只要不是为空，所有类型转换都为true
        if (jsonValue.isNull())
        {
            return false;
        }
        if (jsonValue.isNumeric())
        {
            //包括bool,double int类型
            return jsonValue.asBool();
        }
        if (jsonValue.isString())
        {
            //JSon中认为字符串只有为空的时候才是false，现在规定，只有为true(大小写不敏感)时，才为true，否则为false
            return StringUtil::Equal(jsonValue.asCString(), "true", false);
        }
        return bDefault;
    }
    
    int CSQL::ToInt(const Json::Value& jsonValue, int nDefault)
    {
        try
        {
            //成功情况包括：空、bool、double、int
            return jsonValue.asInt();
        }
        catch (std::exception&)
        {
            //Type is not convertible to int
            if (jsonValue.isString())
            {
                return StringUtil::lexical_cast<int>(jsonValue.asString(), nDefault);
            }
        }
        return nDefault;
    }
    
    double CSQL::ToDouble(const Json::Value& jsonValue, double dDefault)
    {
        try
        {
            //成功情况包括：空、bool、double、int
            return jsonValue.asDouble();
        }
        catch (std::exception&)
        {
            //Type is not convertible to double
            if (jsonValue.isString())
            {
                return StringUtil::lexical_cast<double>(jsonValue.asString(), dDefault);
            }
        }
        return dDefault;
    }
    
    std::string CSQL::ToString(const Json::Value& jsonValue, const std::string& strDefault, bool bBoolTypeTo01)
    {
        try
        {
            //NULL和字符串转换成功
            return jsonValue.asString();
        }
        catch (std::exception&)
        {
            //Type is not convertible to string
            if (jsonValue.isBool())
            {
                static std::string str0 = "0";
                static std::string str1 = "1";
                static std::string strTrue = "true";
                static std::string strFalse = "false";
                if (bBoolTypeTo01)
                {
                    return jsonValue.asBool() ? str1 : str0;
                }
                return jsonValue.asBool() ? strTrue : strFalse;
            }
            if (jsonValue.isInt())
            {
                return StringUtil::lexical_cast<std::string>(jsonValue.asInt(), strDefault);
            }
            if (jsonValue.isDouble())
            {
                return StringUtil::lexical_cast<std::string>(jsonValue.asDouble(), strDefault);
            }
        }
        return strDefault;
    }

}
