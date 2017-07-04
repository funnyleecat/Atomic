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

    //SQL������ñ�ǩ����ӦSCRIPT_CONF_SQL_FLAG��ǩ
    class CSQL
    {
        typedef boost::shared_ptr<CStatment> CStatmentPtr;         //SQL�־�����ָ��        
        typedef std::map<unsigned int, CStatmentPtr> CStatmentMap; //key: index��Value��SQL�־�����ָ�����

    public:
        //����һ�����ó�ʼ�����󣬲�����SQL���ID
        unsigned int Init(TiXmlElement* pXmlSQL);

        //����ʵ�Σ���������β�ִ�����ݿ����������ȡʵ��
        void Execute(DBUtils::CDBStatement* pCDBStatement, const std::string& strSQL, const ArgMap& argMap, long lTimeout) const;

        //��ȡ����SQL��Ϣ        
        void GetSQLInfo(std::string& strSQL, ArgMap& argMap) const;

        //��ȡʵ��SQL��Ϣ
        void GetSQLInfo(std::string& strSQL, ArgMap& argMap, const Json::Value& jValue) const;

    private:
        //SQL�־�MAP
        CStatmentMap m_CStatmentMap;

        //��ȡSQL���ID
        unsigned int GetId(TiXmlElement* pXmlSQL);

        //����SQL�Ӿ��ǩ��ȡ�Ӿ�����ָ�����
        CStatmentPtr GetCStatmentPtr(TiXmlElement *pXmlStatment);

        //����ʵ�ΰ�ִ�в���
        void BindValues(DBUtils::CDBStatement* pCDBStatement, const ArgMap& argMap) const;

        //Json����תboolֵ
        static bool ToBool(const Json::Value& jsonValue, bool bDefault = false);

        //Json����תintֵ
        static int ToInt(const Json::Value& jsonValue, int nDefault = 0);

        //Json����תdoubleֵ
        static double ToDouble(const Json::Value& jsonValue, double dDefault = 0);

        //Json����תstringֵ
        static std::string ToString(const Json::Value& jsonValue, const std::string& strDefault = std::string(), bool bBoolTypeTo01 = false);
    };

    typedef std::map<unsigned int, CSQL> CSQLMap; //key: nId��Value��SQL������
}