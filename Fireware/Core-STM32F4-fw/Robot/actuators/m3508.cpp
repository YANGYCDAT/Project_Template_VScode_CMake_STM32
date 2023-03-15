#include "m3508.h"
#include "can_interface.h"



/**
 * @brief Update the motor speed
 *
 * @param float speed: the input speed of the motor reducer
 */
void M3508::SpeedUpdate(float speed)
{
    m_speed_current = speed / m_reduction_ratio;
}



/**
 * @brief Update the motor angle
 *
 * @param float value: the feedback encoder value
 */
void M3508::AngleUpdate(float value)
{
    m_encoder->EncodeValueUpdate(value);
    m_angle_current = (m_encoder->m_sum_value - m_encoder->m_zero_value) / 
                  m_encoder->m_resolution * 360.0f / m_reduction_ratio;
}



/**
 * @brief Update the motor angle
 *
 * @param 
 */
void M3508::SpeedControl(void)
{
    m_speed_pid->CalWeakenPID(m_speed_target - m_speed_current);
    CANContext* context = GetCANContext(m_hcan);

    // Send the current to motor
    if (m_id >= 1 && m_id <= 4) {
        context->tx_header.StdId = 0x200;
        context->tx_data[(m_id - 1) * 2] = (uint8_t)((int16_t)m_speed_pid->m_output >> 8);
        context->tx_data[(m_id - 1) * 2 + 1] = (uint8_t)((int16_t)m_speed_pid->m_output);
    } else if (m_id >= 5 && m_id <= 8) {
        context->tx_header.StdId = 0x1FF;
        context->tx_data[(m_id - 5) * 2] = (uint8_t)((int16_t)m_speed_pid->m_output >> 8);
        context->tx_data[(m_id - 5) * 2 + 1] = (uint8_t)((int16_t)m_speed_pid->m_output);
    }
    CanSendMessage(context);
}



/**
 * @brief Update the motor angle
 *
 * @param 
 */
void M3508::AngleControl(void)
{
    m_td->CalAdrcTD(m_angle_target);
    m_angle_pid->CalWeakenPID(m_td->m_x1 - m_angle_current);
    m_speed_target = m_angle_pid->m_output;
    m_speed_pid->CalWeakenPID(m_speed_target - m_speed_current);
    CANContext* context = GetCANContext(m_hcan);

    // Send the current to motor
    if (m_id >= 1 && m_id <= 4) {
        context->tx_header.StdId = 0x200;
    } else if (m_id >= 5 && m_id <= 8) {
        context->tx_header.StdId = 0x1FF;
    }
    context->tx_data[(m_id - 1) * 2] = (uint8_t)((int16_t)m_speed_pid->m_output >> 8);
    context->tx_data[(m_id - 1) * 2 + 1] = (uint8_t)((int16_t)m_speed_pid->m_output);
    CanSendMessage(context);
}



/**
 * @brief disable the motor control
 *
 * @param 
 */
void M3508::DisableControl(void) {
    CANContext* context = GetCANContext(m_hcan);

    // Send the current to motor
    if (m_id >= 1 && m_id <= 4) {
        context->tx_header.StdId = 0x200;
    } else if (m_id >= 5 && m_id <= 8) {
        context->tx_header.StdId = 0x1FF;
    }
    context->tx_data[(m_id - 1) * 2] = 0;
    context->tx_data[(m_id - 1) * 2 + 1] = 0;
    CanSendMessage(context);
}