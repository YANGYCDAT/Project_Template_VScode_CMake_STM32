#include "common_inc.h"
#include "vofa.h"


void Vofa::SendData(void)
{
    HAL_UART_Transmit_DMA(m_huart, (unsigned char*)&m_data_send_frame, m_data_send_size);
}