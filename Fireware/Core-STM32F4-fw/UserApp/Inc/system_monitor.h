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
	DECLARE_MONITOR(DataVisualTask);
	DECLARE_MONITOR(LEDTask);

	// 任务执行时间监视
	DECLARE_EXECUTE_TIME(SystemMonitorTask);
	DECLARE_EXECUTE_TIME(DataVisualTask);
	DECLARE_EXECUTE_TIME(LEDTask);

	// 中断监视
	DECLARE_MONITOR(UART4_rx);
    DECLARE_MONITOR(UART5_rx);

	// 系统时间
	unsigned int SysTickTime;
} SystemMonitor;

#endif