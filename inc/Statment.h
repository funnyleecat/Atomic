#pragma once

#include "SQLInfo.h"

class TiXmlElement;

namespace ATOMIC
{
    //SQL�Ӿ����ñ�ǩ����ӦSCRIPT_CONF_STATMENT��ǩ
    class CStatment
    {
    public:
        CStatment();
        virtual ~CStatment();

    public:
        //����һ�����ó�ʼ�����󣬲�����SQL�Ӿ�index
        virtual unsigned int Init(TiXmlElement *pXmlStatment);

        //�������û�ȡSQL��Ϣ
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const;

        //����ʵ�μ��βΣ���������ִ�е�SQL,����true��ʾ�ò��������Ϊ���ղ����б��һԱ���˺���Ϊ��������ò�������֮������
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const;

    protected:
        //SQL���
        std::string m_strSQL;
        //���ñ�ǩ
        std::string m_strFlag;

        //��ȡ�Ӿ�index
        unsigned int GetIndex(TiXmlElement* pXmlStatment);

        //��ȡSQL���
        bool GetSQL(TiXmlElement* pXmlStatment);

    };
}

