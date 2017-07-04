#include "Required.h"
#include "ConfDef.hpp"

#include <workexception.hpp>

namespace ATOMIC
{

    CRequired::CRequired()
    {
        m_strFlag = SCRIPT_CONF_STATMENT_REQUIRED;
    }

    CRequired::~CRequired()
    {

    }

    unsigned int CRequired::Init(TiXmlElement *pXmlStatment)
    {
        unsigned int nIndex = COptional::Init(pXmlStatment);
        GetDefault(pXmlStatment);
        return nIndex;
    }

    bool CRequired::GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const
    {
        bool bRet = COptional::GetSQLInfo(strSQL, sqlArg);
        sqlArg.jValue = m_jDefault;
        return bRet;
    }

    bool CRequired::GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const
    {
        sqlArg.pName = m_strName.c_str();
        sqlArg.eType = m_eType;
        sqlArg.eDirectoion = m_eDirectoion;
        sqlArg.jValue.clear();
        strSQL = m_strSQL;

        if (DBUtils::D_OUT == m_eDirectoion)
        {
            //作为出参，不管有没有传过来，都使用默认配置参数
            return true;
        }
        //作为入参、出入参，有以下情况
        if (jsonActual.isMember(m_strName))
        {
            //参数存在
            if (jsonActual[m_strName].empty())
            {
                //参数值为空
                if (m_jDefault.empty())
                {
                    //默认值为空，抛出异常
                    throw Utils::CWorkException("ARG[%s] VALUE is empty!", m_strName.c_str());
                }

                //默认值不为空，使用默认值
                sqlArg.jValue = m_jDefault;
                return true;
            }

            //参数值不为空，正常接收
            sqlArg.jValue = jsonActual[m_strName];
            return true;
        }

        //参数不存在，抛出异常
        throw Utils::CWorkException("ARG[%s] is not exist!", m_strName.c_str());

        return false;
    }

    void CRequired::GetDefault(TiXmlElement *pXmlStatment)
    {
        const char* pArgDefault = pXmlStatment->Attribute(SCRIPT_CONF_ARG_ATTR_DEGAULT);
        if (pArgDefault && 0 != strlen(pArgDefault))
        {
            m_jDefault = pArgDefault;
        }
        return;
    }

}
