#pragma once

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t LED_Task_Handle;
#define LED_TASK_CYCLE 500
#define DataVisual_TASK_CYCLE 1

void LaunchAllTasks(void);

