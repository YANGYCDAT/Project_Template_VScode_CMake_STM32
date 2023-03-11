#pragma once

#include "usart.h"

#define VOFA_DATA_SEND_FLOAT_NUM ( 16 )
#define VOFA_DATA_RECEIVE_SIZE ( 50 )

class Vofa {
public:
    struct VofaDataSendFrame {
        float m_data[VOFA_DATA_SEND_FLOAT_NUM];  
        unsigned char m_tail[4];
    };


    unsigned char m_data_send_size = VOFA_DATA_SEND_FLOAT_NUM * 4 + 4;
    VofaDataSendFrame m_data_send_frame = {.m_data = {0}, .m_tail = {0x00, 0x00, 0x80, 0x7F}};

    Vofa(){};
    Vofa(UART_HandleTypeDef *huart) { m_huart = huart; };

    void SetUartHandle(UART_HandleTypeDef *huart) { m_huart = huart; };
    void SendData(void);

private:
    UART_HandleTypeDef* m_huart;
};