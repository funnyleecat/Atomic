#pragma once

#include "Optional.h"

namespace ATOMIC
{
    //SQL子句必填参数配置标签，对应SCRIPT_CONF_STATMENT_REQUIRED标签
    class CRequired : public COptional
    {
    public:
        CRequired();
        virtual ~CRequired();
        virtual unsigned int Init(TiXmlElement *pXmlStatment);
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg) const;
        virtual bool GetSQLInfo(std::string& strSQL, CSQLInfo::Arg& sqlArg, const Json::Value& jsonActual) const;
    private:
        Json::Value m_jDefault;                  //参数值，形参时为默认值，实参时为实际值，不使用string是为减少类型转换，sizeof=24

        //获取默认值
        void GetDefault(TiXmlElement *pXmlStatment);
    };
}