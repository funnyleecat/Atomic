#pragma once

#include "Statment.h"

namespace ATOMIC
{
    //SQL子句可选参数配置标签，对应SCRIPT_CONF_STATMENT_OPTIONAL标签
    class COptional : public virtual CStatment
    {
    public:
        COptional();
        virtual ~COptional();
        virtual unsigned int Init(TiXmlElement *pXmlStatment);
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const;
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const;
    protected:
        std::string m_strName;                   //参数名称，对应required和optional标签的name属性值
        DBUtils::DataType m_eType;             //参数类型，对应required和optional标签的type属性值
        DBUtils::BindDirecation m_eDirectoion; //参数类型，对应required和optional标签的directoion属性值，直接使用是为避免转换

        //获取参数类型，无异常跑出
        static DBUtils::DataType GetArgType(const char* pType);

        //获取参数方向，无异常跑出
        static DBUtils::BindDirecation GetArgDirectoion(const char* pDirectoion);
        
        //获取参数配置
        void GetArg(TiXmlElement *pXmlStatment, unsigned int nIndex);

  
    };
}