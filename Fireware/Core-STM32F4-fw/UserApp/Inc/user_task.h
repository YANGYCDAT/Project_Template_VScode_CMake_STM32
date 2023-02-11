#pragma once

#include "FreeRTOS.h"
#include "task.h"

extern TaskHandle_t LED_Task_Handle;
#define LED_TASK_CYCLE 500


void launchAllTasks(void);

