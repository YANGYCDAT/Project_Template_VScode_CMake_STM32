#include "common_inc.h"
#include "uart_protocol.h"
#include "usart.h"

extern DMA_HandleTypeDef hdma_usart3_rx;
/**
 * @brief Decode the datas from the navigation computer
 *
 * @param NULL
 */
void UART_NavigationDataDecode(u8* buffer)
{
	if(	uart3_dma_rec_buffer[0]==0x55 && uart3_dma_rec_buffer[1]==0x00) {
        HAL_UART_DMAStop(&huart3); 
		uint32_t temp  =  __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);   // Reset the buffer
		memcpy(&(Global::navigation.m_data_receive_frame), (u8*)uart3_dma_rec_buffer, sizeof(Global::navigation.m_data_receive_frame));	
        HAL_UART_Receive_DMA(&huart3, uart3_dma_rec_buffer, UART3_DMA_REC_BUFFER_SIZE);
    }	
}



/**
 * @brief Decode the datas from the aim assist computer
 *
 * @param NULL
 */
void UART_AimAssitDataDecode(u8* buffer)
{
    
}