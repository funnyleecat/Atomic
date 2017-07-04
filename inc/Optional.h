#pragma once

#include "Statment.h"

namespace ATOMIC
{
    //SQL�Ӿ��ѡ�������ñ�ǩ����ӦSCRIPT_CONF_STATMENT_OPTIONAL��ǩ
    class COptional : public virtual CStatment
    {
    public:
        COptional();
        virtual ~COptional();
        virtual unsigned int Init(TiXmlElement *pXmlStatment);
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const;
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const;
    protected:
        std::string m_strName;                   //�������ƣ���Ӧrequired��optional��ǩ��name����ֵ
        DBUtils::DataType m_eType;             //�������ͣ���Ӧrequired��optional��ǩ��type����ֵ
        DBUtils::BindDirecation m_eDirectoion; //�������ͣ���Ӧrequired��optional��ǩ��directoion����ֵ��ֱ��ʹ����Ϊ����ת��

        //��ȡ�������ͣ����쳣�ܳ�
        static DBUtils::DataType GetArgType(const char* pType);

        //��ȡ�����������쳣�ܳ�
        static DBUtils::BindDirecation GetArgDirectoion(const char* pDirectoion);
        
        //��ȡ��������
        void GetArg(TiXmlElement *pXmlStatment, unsigned int nIndex);

  
    };
}