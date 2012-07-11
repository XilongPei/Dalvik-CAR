
#include "CTestBasicType.h"
ECode CTestBasicType::boolNon(
    /* [in] */ Boolean i,
    /* [out] */ Boolean * pO)
{
    // TODO: Add your code here
    *pO = i?FALSE:TRUE;
    return NOERROR;
}

ECode CTestBasicType::boolAnd(
    /* [in] */ Boolean i,
    /* [in] */ Boolean j,
    /* [out] */ Boolean * pO)
{
    *pO = i && j;
    return NOERROR;
}

ECode CTestBasicType::boolOr(
    /* [in] */ Boolean i,
    /* [in] */ Boolean j,
    /* [out] */ Boolean * pO)
{
    *pO = i || j;
    return NOERROR;
}

ECode CTestBasicType::strCopy(
    /* [in] */ String i,
    /* [out] */ String * pO)
{
    // TODO: Add your code here
    *pO = String::Duplicate(i); 
    return NOERROR;
}

ECode CTestBasicType::strCon(
    /* [in] */ String i,
    /* [in] */ String j,
    /* [out] */ String * pO)
{
    // TODO: Add your code here
    StringBuf_<2> strBuf;
    strBuf.Append(i);
    strBuf.Append(j);
//    *pO = new String(strBuf);
    return NOERROR;
}

ECode CTestBasicType::strStartwith(
    /* [in] */ String i,
    /* [in] */ String j,
    /* [out] */ Boolean * pO)
{
    *pO = i.Contains(j);
    return NOERROR;
}

