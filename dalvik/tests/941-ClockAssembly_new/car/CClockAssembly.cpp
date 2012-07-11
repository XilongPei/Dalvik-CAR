
#include "CClockAssembly.h"
#include "stdio.h"

ECode CClockAssembly::SetTimeTick(
    /* [in] */ Int32 interval)
{
    // TODO: Add your code here
    return E_NOT_IMPLEMENTED;
}

ECode CClockAssembly::SetAlarm()
{
    printf("CClockAssembly setAlarm...\n");
    Callback::Alarm();
    return NOERROR;
}

