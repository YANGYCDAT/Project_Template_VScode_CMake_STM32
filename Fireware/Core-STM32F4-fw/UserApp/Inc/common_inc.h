#ifndef COMMON_INC_H
#define COMMON_INC_H

#ifdef __cplusplus
extern "C" {
#endif
/*---------------------------- C Scope ---------------------------*/
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stdint-gcc.h"
#include "user_main.h"

#ifdef __cplusplus
}
#endif



/*---------------------------- C++ Scope ---------------------------*/
#include "global.h"
#include "system_monitor.h"
#include "led.h"
#include "user_task.h"





typedef unsigned char  		u8;                  // defined for unsigned 8-bits integer variable
typedef signed   char  		s8;                  // defined for signed 8-bits integer variable	
typedef unsigned short 		u16;                // defined for unsigned 16-bits integer variable
typedef signed   short 		s16;                // defined for signed 16-bits integer variable
typedef unsigned int   		u32;                  // defined for unsigned 32-bits integer variable 
typedef int   				s32;                  // defined for signed 32-bits integer variable 
typedef float          		FP32;                    // single precision floating point variable (32bits)
typedef double         		DB64;                    // double precision floating point variable (64bits) 

#endif