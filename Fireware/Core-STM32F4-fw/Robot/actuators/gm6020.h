#pragma once
#include "pid.h"
#include "adrc.h"
#include "can.h"
#include "encoder.h"
#include "adrc.h"


class GM6020 {
public:
    float m_speed_target;
    float m_speed_current;
    float m_angle_current;
    float m_angle_target;

	float m_reduction_ratio; // motor reducer reduction ratio

    Adrc_TD* m_td;
    Pid* m_speed_pid;
    Pid* m_angle_pid;
    
    /* add other control algorithms */

    /* add other control algorithms */

    CAN_HandleTypeDef* m_hcan;
    AbsEncoder* m_encoder;
    uint32_t m_id;
    uint32_t m_state_update_times;

    void SpeedUpdate(float speed);
    void AngleUpdate(float value);
    void SpeedControl(void);
    void AngleControl(void);
    void DisableControl(void);

    GM6020(CAN_HandleTypeDef* hcan, uint32_t id, uint32_t ration) { 
        m_hcan = hcan;
        m_id = id;
        m_reduction_ratio = ration;
        m_state_update_times = 0;
    };
    ~GM6020();
};