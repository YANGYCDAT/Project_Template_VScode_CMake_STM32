#include "common_inc.h"
#include "user_task.h"


#define TASK_CREATE(NAME, FUNCTION, STACK_SIZE, PARAMETER, PRIORITY, HANDLE) xTaskCreate(\
(TaskFunction_t)(FUNCTION), (const char*)(NAME), (u16)(STACK_SIZE), (void*)(PARAMETER),\
(UBaseType_t)(PRIORITY), (TaskHandle_t*	) &(HANDLE))

TaskHandle_t LED_Task_Handle;
TaskHandle_t DataVisual_Task_Handle;
TaskHandle_t RobotControl_Task_Handle;



/**
 * @brief Data visual task
 *
 * @param NULL
 */
void DataVisual_Task(void) {
	static u32 TaskStartTime;
	const TickType_t RouteTimes = pdMS_TO_TICKS(DataVisual_TASK_CYCLE);

	while(1)
	{
		TaskStartTime = TIME();
		
		// the ID of mdata should be less than 15
		Global::vofa.m_data_send_frame.m_data[0] = Global::system_monitor.CAN1_rx_fps;
		Global::vofa.m_data_send_frame.m_data[1] = Global::system_monitor.CAN2_rx_fps;
		Global::vofa.m_data_send_frame.m_data[2] = Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->m_speed_target;
		Global::vofa.m_data_send_frame.m_data[3] = Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->m_speed_current;
		Global::vofa.m_data_send_frame.m_data[4] = Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->m_angle_current;
		Global::vofa.m_data_send_frame.m_data[5] = Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->m_angle_target;
		Global::vofa.m_data_send_frame.m_data[6] = Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->m_speed_pid->m_output;
		Global::vofa.m_data_send_frame.m_data[7] = Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->m_speed_target;
		Global::vofa.m_data_send_frame.m_data[8] = Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->m_speed_current;
		

		Global::vofa.m_data_send_frame.m_data[15] = Global::system_monitor.SysTickTime;
		Global::vofa.SendData();

		Global::system_monitor.DataVisualTask_cnt++; // Statistic task execution times
		Global::system_monitor.DataVisualTask_ExecuteTime = TIME() - TaskStartTime; // Caculate the execution time of this task
		
		vTaskDelay(RouteTimes);
	}
}



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
 * @brief Robot control task
 *
 * @param NULL
 */
void RobotControl_Task(void) {
	static u32 TaskStartTime;
	const TickType_t RouteTimes = pdMS_TO_TICKS(RobotControl_TASK_CYCLE);

	while(1)
	{
		TaskStartTime = TIME();
		
		// Update the robot state
		Global::sentry.StateUpdate();
		// Chassis control
		Global::sentry.MoveChassis();
		// Gimbal control
		Global::sentry.MoveGimbal();

		Global::system_monitor.RobotControlTask_cnt++; // Statistic task execution times
		Global::system_monitor.RobotControlTask_ExecuteTime = TIME() - TaskStartTime; // Caculate the execution time of this task
		
		vTaskDelay(RouteTimes);
	}
}



/**
 * @brief Launch all the user tasks 
 *
 * @param NULL
 */
void LaunchAllTasks(void) {
	taskENTER_CRITICAL(); // Enter task critical section

    TASK_CREATE("LED", LED_Task, 200, NULL, 1, LED_Task_Handle); // Create LED task
	TASK_CREATE("DataVisual", DataVisual_Task, 200, NULL, 2, DataVisual_Task_Handle); // Create data visual task
	TASK_CREATE("RobotControl", RobotControl_Task, 200, NULL, 2, RobotControl_Task_Handle); // Create data visual task

	taskEXIT_CRITICAL(); // Exit task critical section

	vTaskStartScheduler(); // Start FreeRTOS scheduler to launch all tasks
}