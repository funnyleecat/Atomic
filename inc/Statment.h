#pragma once

#include "SQLInfo.h"

class TiXmlElement;

namespace ATOMIC
{
    //SQL子句配置标签，对应SCRIPT_CONF_STATMENT标签
    class CStatment
    {
    public:
        CStatment();
        virtual ~CStatment();

    public:
        //根据一个配置初始化对象，并返回SQL子句index
        virtual unsigned int Init(TiXmlElement *pXmlStatment);

        //根据配置获取SQL信息
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const;

        //根据实参及形参，返回最终执行的SQL,返回true表示该参数将会成为最终参数列表的一员，此函数为本库的配置参数精华之所在啦
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const;

    protected:
        //SQL语句
        std::string m_strSQL;
        //配置标签
        std::string m_strFlag;

        //获取子句index
        unsigned int GetIndex(TiXmlElement* pXmlStatment);

        //获取SQL语句
        bool GetSQL(TiXmlElement* pXmlStatment);

    };
}

