#include "vofa.h"



/**
 * @brief Send data to Vofa+
 *
 * @param NULL
 */
void Vofa::SendData(void)
{
    HAL_UART_Transmit_DMA(m_huart, (unsigned char*)&m_data_send_frame, m_data_send_size);
}