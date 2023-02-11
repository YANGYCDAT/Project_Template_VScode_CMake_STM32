#include "common_inc.h"
#include "print.h"

void Print::PrintAllTasksFps(void)
{
    printf("LED task pfs: %d\n", Global::system_monitor.LEDTask_fps);

    printf("Current time: %d\n", Global::system_monitor.SysTickTime);
}