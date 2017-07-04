#pragma once

#include "Optional.h"

namespace ATOMIC
{
    //SQL�Ӿ����������ñ�ǩ����ӦSCRIPT_CONF_STATMENT_REQUIRED��ǩ
    class CRequired : public COptional
    {
    public:
        CRequired();
        virtual ~CRequired();
        virtual unsigned int Init(TiXmlElement *pXmlStatment);
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const;
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const;
    private:
        Json::Value m_jDefault;                  //����ֵ���β�ʱΪĬ��ֵ��ʵ��ʱΪʵ��ֵ����ʹ��string��Ϊ��������ת����sizeof=24

        //��ȡĬ��ֵ
        void GetDefault(TiXmlElement *pXmlStatment);
    };
}