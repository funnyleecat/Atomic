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
            //��Ϊ���Σ�������û�д���������ʹ��Ĭ�����ò���
            return true;
        }
        //��Ϊ��Ρ�����Σ����������
        if (jsonActual.isMember(m_strName))
        {
            //��������
            if (jsonActual[m_strName].empty())
            {
                //����ֵΪ��
                if (m_jDefault.empty())
                {
                    //Ĭ��ֵΪ�գ��׳��쳣
                    throw Utils::CWorkException("ARG[%s] VALUE is empty!", m_strName.c_str());
                }

                //Ĭ��ֵ��Ϊ�գ�ʹ��Ĭ��ֵ
                sqlArg.jValue = m_jDefault;
                return true;
            }

            //����ֵ��Ϊ�գ���������
            sqlArg.jValue = jsonActual[m_strName];
            return true;
        }

        //���������ڣ��׳��쳣
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
