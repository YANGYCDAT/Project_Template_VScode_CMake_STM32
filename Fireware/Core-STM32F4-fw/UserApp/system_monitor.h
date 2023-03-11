#ifndef OS_TYPES_H
#define OS_TYPES_H

#include "core_cm4.h"

// 系统监视器时间源
#define TIME() TIM5->CNT

// 系统监视
#define DECLARE_MONITOR(name) 		unsigned int name##_cnt; unsigned int name##_fps
#define DECLARE_EXECUTE_TIME(name)	unsigned int name##_ExecuteTime

// 任务帧率统计结构体
typedef struct
{		
	// 任务执行频率监视
	DECLARE_MONITOR(SystemMonitorTask);
	DECLARE_MONITOR(DataVisualizeTask);
	DECLARE_MONITOR(LEDTask);
	DECLARE_MONITOR(RobotControlTask);
	DECLARE_MONITOR(DataCommunicateTask);

	// 任务执行时间监视
	DECLARE_EXECUTE_TIME(SystemMonitorTask);
	DECLARE_EXECUTE_TIME(DataVisualizeTask);
	DECLARE_EXECUTE_TIME(LEDTask);
	DECLARE_EXECUTE_TIME(RobotControlTask);
	DECLARE_EXECUTE_TIME(DataCommunicateTask);

	// 中断监视
	DECLARE_MONITOR(UART1_rx);
	DECLARE_MONITOR(UART2_rx);
	DECLARE_MONITOR(UART3_rx);
	DECLARE_MONITOR(UART4_rx);
    DECLARE_MONITOR(UART5_rx);
	DECLARE_MONITOR(UART6_rx);
	
	DECLARE_MONITOR(CAN1_rx);
	DECLARE_MONITOR(CAN2_rx);

	// 系统时间
	unsigned int SysTickTime;
} SystemMonitor;

#endif