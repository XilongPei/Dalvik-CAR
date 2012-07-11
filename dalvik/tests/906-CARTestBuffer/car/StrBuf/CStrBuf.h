
#ifndef __CSTRBUF_H__
#define __CSTRBUF_H__

#include "_CStrBuf.h"

CarClass(CStrBuf)
{
public:
    CARAPI addStr(
        /* [in] */ String i,
        /* [out] */ StringBuf * pO);

private:
    // TODO: Add your private member variables here.
};

#endif // __CSTRBUF_H__
