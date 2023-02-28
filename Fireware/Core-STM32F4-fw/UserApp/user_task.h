#pragma once

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t LED_Task_Handle;
#define LED_TASK_CYCLE 500
#define DataVisualize_TASK_CYCLE 1
#define RobotControl_TASK_CYCLE 1
#define DataCommunicate_TASK_CYCLE 10

void LaunchAllTasks(void);

