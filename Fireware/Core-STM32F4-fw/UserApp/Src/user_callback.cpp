#include "common_inc.h"
#include "user_callback.h"

#define DETECT_MONITOR(name) Global::system_monitor.name##_fps = \
Global::system_monitor.name##_cnt; Global::system_monitor.name##_cnt = 0

extern "C" {
    extern void xPortSysTickHandler(void);
}



/**
 * @brief SysTick interruption User callback function
 *
 * @param NULL
 */
void sysTickCallback(void) 
{
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)			
    {
        xPortSysTickHandler(); // System task scheduling processing
    }
	if(Global::system_monitor.SysTickTime % 1000 == 0) // Calculate the rate of monitored items 
	{
		/** Main Task Monitor */
		DETECT_MONITOR(DataVisualTask);
		DETECT_MONITOR(LEDTask);
		
		/** IT Monitor */

		DETECT_MONITOR(UART4_rx);
		DETECT_MONITOR(UART5_rx);
	}

	Global::system_monitor.SysTickTime++;
}
