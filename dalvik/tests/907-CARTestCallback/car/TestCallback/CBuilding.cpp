
#include "CBuilding.h"
#include <stdio.h>
ECode CBuilding::CatchFire()
{
    printf("The building is on fire!\n");

    Callback::EmployeeEvent();    //����Employee()�ص��¼�
    Callback::FiremanEvent();     //����Fireman()�ص��¼�

    return NOERROR;
}

