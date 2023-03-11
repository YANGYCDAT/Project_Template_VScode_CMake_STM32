#include "uart_interface.h"

unsigned char uart1_dma_rec_buffer[UART1_DMA_REC_BUFFER_SIZE];
unsigned char uart2_dma_rec_buffer[UART2_DMA_REC_BUFFER_SIZE];
unsigned char uart3_dma_rec_buffer[UART3_DMA_REC_BUFFER_SIZE];
unsigned char uart4_dma_rec_buffer[UART4_DMA_REC_BUFFER_SIZE];
unsigned char uart5_dma_rec_buffer[UART5_DMA_REC_BUFFER_SIZE];
unsigned char uart6_dma_rec_buffer[UART6_DMA_REC_BUFFER_SIZE];


/**
  * @brief  dr16 uart dma configration
  * @param
  * @retval error code
  */
int UART_Receive_DMA_No_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Size)
{
    uint32_t tmp = 0;

    tmp = huart->RxState;
    if (tmp == HAL_UART_STATE_READY)
    {
        if ((pData == NULL) || (Size == 0))
        {
            return HAL_ERROR;
        }

        /* Process Locked */
        __HAL_LOCK(huart);

        huart->pRxBuffPtr = pData;
        huart->RxXferSize = Size;

        huart->ErrorCode = HAL_UART_ERROR_NONE;

        /* Enable the DMA Stream */
        HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR,
                      (uint32_t)pData, Size);

        /* Enable the DMA transfer for the receiver request by setting the DMAR bit
        in the UART CR3 register */
        SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

        /* Process Unlocked */
        __HAL_UNLOCK(huart);

        return HAL_OK;
    }
    else
    {
        return HAL_BUSY;
    }
}