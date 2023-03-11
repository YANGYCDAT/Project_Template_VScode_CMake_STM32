#pragma once

#include "usart.h"

#define NAVIGATION_DATA_SEND_FLOAT_NUM          ((uint8_t)8)
#define NAVIGATION_DATA_RECEIVE_FLOAT_NUM       ((uint8_t)8)
#define NAVIGATION_DATA_RECEIVE_SIZE            ((uint8_t)6 + 4 * NAVIGATION_DATA_RECEIVE_FLOAT_NUM)


class Navigation {
public:
    #pragma pack(1)
    struct NavigationDataSendFrame {
        unsigned char m_head[2];
        unsigned char m_id;
        unsigned char m_length;
        float m_data[NAVIGATION_DATA_SEND_FLOAT_NUM];  
        unsigned char m_tail[2];
    };
    struct NavigationDataReceiveFrame {
        unsigned char m_head[2];
        unsigned char m_id;
        unsigned char m_length;
        float m_data[NAVIGATION_DATA_RECEIVE_FLOAT_NUM];  
        unsigned char m_tail[2];
    };
    #pragma pack()

    unsigned char m_data_send_size = NAVIGATION_DATA_SEND_FLOAT_NUM * 4 + 6;
    NavigationDataSendFrame m_data_send_frame = {.m_head = {0x55, 0x00}, .m_id = 0x00,
    .m_length = NAVIGATION_DATA_SEND_FLOAT_NUM, .m_data = {0}, .m_tail = {0x00, 0xAA}};
    NavigationDataReceiveFrame m_data_receive_frame = {.m_head = {0x55, 0x00}, .m_id = 0x00,
    .m_length = NAVIGATION_DATA_RECEIVE_FLOAT_NUM, .m_data = {1.23,1.23}, .m_tail = {0x00, 0xAA}};

    Navigation(){};
    Navigation(UART_HandleTypeDef *huart) { m_huart = huart; };

    void SetUartHandle(UART_HandleTypeDef *huart);
    void SendData(void);

private:
    UART_HandleTypeDef* m_huart;
};