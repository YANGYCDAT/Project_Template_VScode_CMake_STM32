#include "vofa.h"


/**
 * @brief Set the UART for Vofa
 *
 * @param UART_HandleTypeDef *huart: UART handle
 */
void Vofa::SetUartHandle(UART_HandleTypeDef *huart)
{
    m_huart = huart; 
}



/**
 * @brief Send data to Vofa+
 *
 * @param NULL
 */
void Vofa::SendData(void)
{
    HAL_UART_Transmit_DMA(m_huart, (unsigned char*)&m_data_send_frame, m_data_send_size);
}