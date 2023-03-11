#pragma once

#include "usart.h"

class DJIRC {
private:
    struct RCChannel {
        uint16_t Ch0;
        uint16_t Ch1;
        uint16_t Ch2;
        uint16_t Ch3;
        uint16_t Ch4;
        uint8_t SW_L;
        uint8_t SW_R;
    };

    UART_HandleTypeDef* m_huart;
    
public:
    RCChannel channel;




    void SetUartHandle(UART_HandleTypeDef *huart) { m_huart = huart; };
};

#define DJI_RC_RECEIVE_SIZE            ((uint8_t)18)

#define RC_CH_VALUE_MIN             ((uint16_t)364)
#define RC_CH_VALUE_OFFSET          ((uint16_t)1024)
#define RC_CH_VALUE_MAX             ((uint16_t)1684)
#define RC_CH_VALUE_DEAD            ((uint16_t)20)
#define RC_CH_VALUE_RANGE           ((uint16_t)660)

#define RC_SW_UP                    ((uint8_t)1)
#define RC_SW_MID                   ((uint8_t)3)
#define RC_SW_DOWN                  ((uint8_t)2)
