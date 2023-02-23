#include "communication.h"
#include "usart.h"
#include "retarget.h"
#include "user_global.h"
#include "can_interface.h"
#include "uart_interface.h"


/**
 * @brief Init all communication staffs,includes interface add protocol
 *
 * @param NULL
 */
void InitCommunication(void)
{
    // Using UART5 for debug input/output
    RetargetInit(&huart5); 

    // Using UART4 for sending visual data to Vofa+
    Global::vofa.SetUartHandle(&huart4); 

    // Specify UART DMA  receive buffer
    HAL_UART_Receive_DMA(&huart4, uart4_dma_rec_buffer, UART4_DMA_REC_BUFFER_SIZE); 
    HAL_UART_Receive_DMA(&huart5, uart5_dma_rec_buffer, UART5_DMA_REC_BUFFER_SIZE); 
    
    // Enable UART IDLE Interruption
    __HAL_UART_ENABLE_IT(&huart4, UART_IT_IDLE);         
    __HAL_UART_ENABLE_IT(&huart5, UART_IT_IDLE);

    // Configure CAN filter
    CAN_Filter_Config(&hcan1, 0);
    CAN_Filter_Config(&hcan2, 14);
    // Init CAN receive message
    can1_context.Init(&hcan1, CAN_ID_STD, CAN_RTR_DATA, 8);
    can2_context.Init(&hcan2, CAN_ID_STD, CAN_RTR_DATA, 8);

    // Start CAN
    HAL_CAN_Start(&hcan1); 
    HAL_CAN_Start(&hcan2); 
	HAL_CAN_ActivateNotification(&hcan1,CAN_IT_RX_FIFO0_MSG_PENDING);
	HAL_CAN_ActivateNotification(&hcan2,CAN_IT_RX_FIFO0_MSG_PENDING);

    printf("Init communication successfully !\n");
}


