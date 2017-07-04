#include "Optional.h"
#include "ConfDef.hpp"

#include <StringFunc.hpp>
#include <workexception.hpp>

namespace ATOMIC
{
    COptional::COptional() :m_eType(DBUtils::DT_Uknown), m_eDirectoion(DBUtils::D_Unknown)
    {
        m_strFlag = SCRIPT_CONF_STATMENT_OPTIONAL;
    }

    COptional::~COptional()
    {

    }

    unsigned int COptional::Init(TiXmlElement *pXmlStatment)
    {
        unsigned int nIndex = GetIndex(pXmlStatment);
        GetSQL(pXmlStatment);
        GetArg(pXmlStatment, nIndex);
        return nIndex;
    }

    bool COptional::GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const
    {
        sqlArg.pName = m_strName.c_str();
        sqlArg.eType = m_eType;
        sqlArg.eDirectoion = m_eDirectoion;
        sqlArg.jValue.clear();
        strSQL = m_strSQL;
        return true;
    }

    bool COptional::GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const
    {
        sqlArg.pName = m_strName.c_str();
        sqlArg.eType = m_eType;
        sqlArg.eDirectoion = m_eDirectoion;
        sqlArg.jValue.clear();
        strSQL = m_strSQL;

        if (DBUtils::D_OUT == m_eDirectoion)
        {
            //��Ϊ���Σ�������û�д���������ʹ��Ĭ�����ò���
            return true;
        }

        //��Ϊ��Ρ�����Σ����������
        if (jsonActual.isMember(m_strName))
        {
            //�������ڣ�����ֵȫ�̽���
            sqlArg.jValue = jsonActual[m_strName];
            return true;
        }

        //���������ڣ����Բ�����SQL
        strSQL.clear();
        return false;
    }

    DBUtils::DataType COptional::GetArgType(const char* pType)
    {
        if (NULL == pType || 0 == strlen(pType))
        {
            return DBUtils::DT_Uknown;
        }
        if (StringUtil::Equal(pType, ARG_TYPE_STR_STR))
        {
            return DBUtils::DT_String;
        }
        if (StringUtil::Equal(pType, ARG_TYPE_INT_STR))
        {
            return DBUtils::DT_INT;
        }
        if (StringUtil::Equal(pType, ARG_TYPE_DOUBLE_STR))
        {
            return DBUtils::DT_DOUBLE;
        }
        if (StringUtil::Equal(pType, ARG_TYPE_DATE_STR))
        {
            return DBUtils::DT_String;
        }
        if (StringUtil::Equal(pType, ARG_TYPE_CURSOR_STR))
        {
            return DBUtils::DT_Cursor;
        }
        return DBUtils::DT_Uknown;
    }

    DBUtils::BindDirecation COptional::GetArgDirectoion(const char* pDirectoion)
    {
        if (NULL == pDirectoion || 0 == strlen(pDirectoion))
        {
            return DBUtils::D_Unknown;
        }
        if (StringUtil::Equal(pDirectoion, ARG_ATTR_DIRECTOION_IN))
        {
            return DBUtils::D_IN;
        }
        if (StringUtil::Equal(pDirectoion, ARG_ATTR_DIRECTOION_INOUT))
        {
            return DBUtils::D_INOUT;
        }
        if (StringUtil::Equal(pDirectoion, ARG_ATTR_DIRECTOION_OUT))
        {
            return DBUtils::D_OUT;
        }
        return DBUtils::D_Unknown;
    }

    void COptional::GetArg(TiXmlElement *pXmlStatment, unsigned int nIndex)
    {
        m_strName.clear();
        m_eType = DBUtils::DT_Uknown;
        m_eDirectoion = DBUtils::D_Unknown;

        //������
        const char* pArgName = pXmlStatment->Attribute(SCRIPT_CONF_ARG_ATTR_NAME);
        if (NULL == pArgName)
        {
            throw Utils::CWorkException("%s Attribute TAG[%s] not found", m_strFlag.c_str(), SCRIPT_CONF_ARG_ATTR_NAME);
        }
        if (0 == strlen(pArgName))
        {
            throw Utils::CWorkException("%s Attribute[%s] value is empty", m_strFlag.c_str(), SCRIPT_CONF_ARG_ATTR_NAME);
        }
        m_strName = pArgName;

        //��������
        const char* pArgType = pXmlStatment->Attribute(SCRIPT_CONF_ARG_ATTR_TYPE);
        m_eType = COptional::GetArgType(pArgType);
        if (DBUtils::DT_Uknown == m_eType)
        {
            throw Utils::CWorkException("%s Attribute[%s] value[%s] is invalid", m_strFlag.c_str(), SCRIPT_CONF_ARG_ATTR_TYPE, pArgType);
        }

        //��������
        const char* pArgDirectoion = pXmlStatment->Attribute(SCRIPT_CONF_ARG_ATTR_DIRECTOION);
        m_eDirectoion = COptional::GetArgDirectoion(pArgDirectoion);
        if (DBUtils::D_Unknown == m_eDirectoion)
        {
            throw Utils::CWorkException("%s Attribute[%s] value[%s] is invalid", m_strFlag.c_str(), SCRIPT_CONF_ARG_ATTR_DIRECTOION, pArgDirectoion);
        }
        return;
    }

}
