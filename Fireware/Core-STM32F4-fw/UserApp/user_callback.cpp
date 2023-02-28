#include "common_inc.h"
#include "user_callback.h"
#include "uart_protocol.h"
#include "can_protocol.h"
#include "can_interface.h"


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
void User_SysTickCallback(void) 
{
	// System task scheduling processing
    if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED) {
        xPortSysTickHandler(); 
    }

	// Calculate the rate of monitored items
	if(Global::system_monitor.SysTickTime % 1000 == 0) {
		// Main Task Monitor
		DETECT_MONITOR(DataVisualizeTask);
		DETECT_MONITOR(LEDTask);
		DETECT_MONITOR(RobotControlTask);
		DETECT_MONITOR(DataCommunicateTask);
		
		// IT Monitor
		DETECT_MONITOR(UART3_rx);
		DETECT_MONITOR(UART4_rx);
		DETECT_MONITOR(UART5_rx);
		DETECT_MONITOR(CAN1_rx);
		DETECT_MONITOR(CAN2_rx);
	}

	Global::system_monitor.SysTickTime++;
}



/**
 * @brief UART RX interruption User callback function
 *
 * @param UART_HandleTypeDef *huart: UART handle
 */
void User_UART_RX_Callback(UART_HandleTypeDef *huart)
{
	// IDLE interrupt
	if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE)) {
		// Clear the IDLE interrupt flag
		__HAL_UART_CLEAR_IDLEFLAG(huart);                     

		// Decode UART datas
		if (huart->Instance == USART3) {
			UART_NavigationDataDecode(uart3_dma_rec_buffer); // Decode navigation data
			Global::system_monitor.UART3_rx_cnt++;
		}else if (huart->Instance == UART4) {
			Global::system_monitor.UART4_rx_cnt++;
		} else if (huart->Instance == UART5) {
			UART_AimAssitDataDecode(uart5_dma_rec_buffer); // Decode aim assit data
			Global::system_monitor.UART5_rx_cnt++;
		}
	} 
}



/**
 * @brief CAN RX interruption User callback function
 *
 * @param NULL
 */
void User_CAN_RX_Callback(CAN_HandleTypeDef* hcan)
{
	if (( READ_REG(hcan->Instance->IER) & CAN_IT_RX_FIFO0_MSG_PENDING) != 0U) {
        /* Check if message is still pending */
        if ((hcan->Instance->RF0R & CAN_RF0R_FMP0) != 0U) {
			// receive message from fifo
			CANContext* context = GetCANContext(hcan);
			HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &(context->rx_header), 
			&(context->rx_data[0]));
			// decode message
			CAN_DataDecode(context);

			if (hcan->Instance == CAN1) {
				Global::system_monitor.CAN1_rx_cnt++;
			} else if (hcan->Instance == CAN2) {
				Global::system_monitor.CAN2_rx_cnt++;
			}
        }
    }
}