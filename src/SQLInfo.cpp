#include "SQLInfo.h"

namespace ATOMIC
{
    CSQLInfo::Arg::Arg() :pName(NULL), eType(DBUtils::DT_Uknown), eDirectoion(DBUtils::D_Unknown)
    {
    }

    CSQLInfo::Arg::operator bool()
    {
        bool bInvalid = (NULL == pName) || (DBUtils::DT_Uknown == eType) || (DBUtils::D_Unknown == eDirectoion);
        return !bInvalid;
    }

    const char* CSQLInfoImpl::GetSQLText() const
    {
        return m_strSQL.c_str();
    }

    unsigned int CSQLInfoImpl::GetArgCount() const
    {
        return (unsigned int)m_argVec.size();
    }

    const CSQLInfo::Arg& CSQLInfoImpl::GetArgInfo(unsigned int uIndex) const
    {
        return m_argVec.at(uIndex);
    }

}
