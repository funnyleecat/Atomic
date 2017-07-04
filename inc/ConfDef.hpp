#pragma once

#include <string>

#define USING_TINYXML_DLL
#include <tinystr.h>
#include <tinyxml.h>

namespace ATOMIC
{
    //�������������ַ���
    static const char ARG_TYPE_UNKNOWN_STR[] = "UNKNOWN";
    static const char ARG_TYPE_STR_STR[] = "STRING";
    static const char ARG_TYPE_INT_STR[] = "INT";
    static const char ARG_TYPE_DOUBLE_STR[] = "DOUBLE";
    static const char ARG_TYPE_DATE_STR[] = "DATE";
    static const char ARG_TYPE_DATE_FORMAT[] = "YYYY-MM-DD HH24:MI:SS";//DATE���͸�ʽ��ģ��
    static const char ARG_TYPE_DATE_FORMAT_OUT[] = "YYYYMMDD";//DATE���͸�ʽ��ģ��
    static const char ARG_TYPE_CURSOR_STR[] = "CURSOR";

    static const char ARG_ATTR_DIRECTOION_IN[] = "IN";       //�������
    static const char ARG_ATTR_DIRECTOION_INOUT[] = "INOUT"; //���������
    static const char ARG_ATTR_DIRECTOION_OUT[] = "OUT";     //��������

    //�ű����ùؼ���
    static const char SCRIPT_CONF_FLAG[] = "ATOMIC";
    static const char SCRIPT_CONF_SQL_FLAG[] = "SQL";
    static const char SCRIPT_CONF_SQL_ID[] = "id";
    static const char SCRIPT_CONF_STATMENT[] = "statment";
    static const char SCRIPT_CONF_STATMENT_OPTIONAL[] = "optional";
    static const char SCRIPT_CONF_STATMENT_REQUIRED[] = "required";
    static const char SCRIPT_CONF_STATMENT_INDEX[] = "index";

    static const char SCRIPT_CONF_NOTE[] = "note";

    static const char SCRIPT_CONF_ARG_ATTR_NAME[] = "name";
    static const char SCRIPT_CONF_ARG_ATTR_TYPE[] = "type";
    static const char SCRIPT_CONF_ARG_ATTR_DIRECTOION[] = "directoion";
    static const char SCRIPT_CONF_ARG_ATTR_DEGAULT[] = "default";
}
