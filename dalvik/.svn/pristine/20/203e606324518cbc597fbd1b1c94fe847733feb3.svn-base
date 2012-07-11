
#include "CBuilding.h"
#include <stdio.h>
ECode CBuilding::CatchFire()
{
    printf("The building is on fire!\n");

    Callback::EmployeeEvent();    //激发Employee()回调事件
    Callback::FiremanEvent();     //激发Fireman()回调事件

    return NOERROR;
}

