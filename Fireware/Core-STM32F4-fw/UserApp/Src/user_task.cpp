#include "common_inc.h"
#include "user_task.h"

// uint8_t ucHeap[ configTOTAL_HEAP_SIZE ]; // define the heap used by FreeRTOS

#define TASK_CREATE(NAME, FUNCTION, STACK_SIZE, PARAMETER, PRIORITY, HANDLE) xTaskCreate(\
(TaskFunction_t)(FUNCTION), (const char*)(NAME), (u16)(STACK_SIZE), (void*)(PARAMETER),\
(UBaseType_t)(PRIORITY), (TaskHandle_t*	) &(HANDLE))

TaskHandle_t LED_Task_Handle;



/**
 * @brief LED task
 *
 * @param NULL
 */
void LED_Task(void) {
	static u32 TaskStartTime;
	const TickType_t RouteTimes = pdMS_TO_TICKS(LED_TASK_CYCLE);
	
	while(1)
	{
		TaskStartTime = TIME();
		
		Global::led.TogglePink();

		Global::system_monitor.LEDTask_cnt++; // Statistic task execution times
		Global::system_monitor.LEDTask_ExecuteTime = TIME() - TaskStartTime; // Caculate the execution time of this task
		
		vTaskDelay(RouteTimes);
	}
}



/**
 * @brief Launch all the user tasks 
 *
 * @param NULL
 */
void launchAllTasks(void) {
    taskENTER_CRITICAL(); // Enter task critical section

    TASK_CREATE("LED", LED_Task, 200, NULL, 1, LED_Task_Handle); // Create LED task

	taskEXIT_CRITICAL(); // Exit task critical section

	vTaskStartScheduler(); // Start FreeRTOS scheduler to launch all tasks
}