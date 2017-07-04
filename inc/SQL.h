#pragma once

#include <map>
#include <json/json.h>
#include <boost/shared_ptr.hpp>

#include "SQLInfo.h"

class TiXmlElement;

namespace DBUtils
{
    class CDBStatement;
}

namespace ATOMIC
{
    class CSQLInfoImpl;
    class CStatment;

    //SQL语句配置标签，对应SCRIPT_CONF_SQL_FLAG标签
    class CSQL
    {
        typedef boost::shared_ptr<CStatment> CStatmentPtr;         //SQL字句智能指针        
        typedef std::map<unsigned int, CStatmentPtr> CStatmentMap; //key: index，Value：SQL字句智能指针对象

    public:
        //根据一个配置初始化对象，并返回SQL语句ID
        unsigned int Init(TiXmlElement* pXmlSQL);

        //根据实参，结合自身形参执行数据库操作，并获取实参
        void Execute(DBUtils::CDBStatement* pCDBStatement, const std::string& strSQL, const ArgMap& argMap, long lTimeout) const;

        //获取配置SQL信息        
        void GetSQLInfo(std::string& strSQL, ArgMap& argMap) const;

        //获取实际SQL信息
        void GetSQLInfo(std::string& strSQL, ArgMap& argMap, const Json::Value& jValue) const;

    private:
        //SQL字句MAP
        CStatmentMap m_CStatmentMap;

        //获取SQL语句ID
        unsigned int GetId(TiXmlElement* pXmlSQL);

        //根据SQL子句标签获取子句智能指针对象
        CStatmentPtr GetCStatmentPtr(TiXmlElement *pXmlStatment);

        //根据实参绑定执行参数
        void BindValues(DBUtils::CDBStatement* pCDBStatement, const ArgMap& argMap) const;

        //Json对象转bool值
        static bool ToBool(const Json::Value& jsonValue, bool bDefault = false);

        //Json对象转int值
        static int ToInt(const Json::Value& jsonValue, int nDefault = 0);

        //Json对象转double值
        static double ToDouble(const Json::Value& jsonValue, double dDefault = 0);

        //Json对象转string值
        static std::string ToString(const Json::Value& jsonValue, const std::string& strDefault = std::string(), bool bBoolTypeTo01 = false);
    };

    typedef std::map<unsigned int, CSQL> CSQLMap; //key: nId，Value：SQL语句对象
}