#pragma once
#include "can.h"

class CANContext {
public:
    CAN_HandleTypeDef* handle;
    CAN_RxHeaderTypeDef rx_header;
    CAN_TxHeaderTypeDef tx_header;

    uint32_t last_mailbos;

    uint8_t rx_data[8];
    uint8_t tx_data[8];

    void Init(CAN_HandleTypeDef* hcan, uint32_t id_type, uint32_t frame_type, uint32_t length);

    CANContext() {};
    ~CANContext() {};
};


void CAN_Filter_Config(CAN_HandleTypeDef* hcan, uint32_t filter_id);
CANContext* GetCANContext(CAN_HandleTypeDef* hcan);
void CanSendMessage(CANContext *p_message);

extern CANContext can1_context;
extern CANContext can2_context;