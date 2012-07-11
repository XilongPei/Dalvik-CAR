
#include "CServer.h"
ECode CServer::compute(
    /* [in] */ Int32 i,
    /* [in] */ Int32 count,
    /* [out] */ Int64 * pO)
{
    // TODO: Add your code here
    Int64 result = 0;
	for(int j = 0; j < count; j++)
	{
		result += i ;
	}
	*pO = result;
    return NOERROR;
}

