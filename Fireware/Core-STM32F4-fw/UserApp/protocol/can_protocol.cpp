#include "common_inc.h"
#include "can_protocol.h"



static s32 GetEncoderNumber(u8* pData);
static s32 GetMotorSpeed(u8* pData);


/**
 * @brief Decode the datas from CAN
 *
 * @param NULL
 */
void CAN_DataDecode(CANContext* context)
{
    if (context->handle->Instance == CAN1) {
        switch(context->rx_header.StdId){
            // case (0x200 + CHASSIS_FLA_MOTOR_ID):	
            //     Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->
            //     AngleUpdate(GetEncoderNumber(&(context->rx_data[0])));
            //     Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->
            //     SpeedUpdate(GetMotorSpeed(&(context->rx_data[0])));
            //     Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->m_state_update_times++;
            //     break;

            // case (0x204 + GIMBAL_YAW_MOTOR_ID): 
            //     Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->
            //     AngleUpdate(GetEncoderNumber(&(context->rx_data[0])));
            //     Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->
            //     SpeedUpdate(GetMotorSpeed(&(context->rx_data[0])));
            //     Global::sentry.gimbal_motor[Global::sentry.GIMBAL_YAW_MOTOR]->m_state_update_times++;
            //     break;

            case 0x205: 

                break;
        }
    } else if (context->handle->Instance == CAN2) {
        switch(context->rx_header.StdId){  
            case (0x200 + CHASSIS_FRA_MOTOR_ID):	
                Global::sentry.chassis_motor[Global::sentry.CHASSIS_FRA_MOTOR]->
                AngleUpdate(GetEncoderNumber(&(context->rx_data[0])));
                Global::sentry.chassis_motor[Global::sentry.CHASSIS_FRA_MOTOR]->
                SpeedUpdate(GetMotorSpeed(&(context->rx_data[0])));
                Global::sentry.chassis_motor[Global::sentry.CHASSIS_FRA_MOTOR]->m_state_update_times++;
                break;              
            case (0x200 + CHASSIS_FLA_MOTOR_ID):	
                Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->
                AngleUpdate(GetEncoderNumber(&(context->rx_data[0])));
                Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->
                SpeedUpdate(GetMotorSpeed(&(context->rx_data[0])));
                Global::sentry.chassis_motor[Global::sentry.CHASSIS_FLA_MOTOR]->m_state_update_times++;
                break;

        }
    }
}



/**
 *@brief Read the motor speed returned by the encoder, the available range is C610, C620, 6020 motor
 *@param pData original data array
 *@return motor speed
*/
s32 GetMotorSpeed(u8* pData)
{
	s32 speed_temp;
	s32 base_value = 0xFFFF;
	if(pData[2] & 0x01<<7 )
	{	speed_temp = (base_value<<16 | pData[2]<<8 | pData[3]);}
	else
	{	speed_temp = pData[2]<<8 | pData[3];}
	return speed_temp;
}



/**
 *@brief Read the mechanical angle returned by the encoder, the available range is C610, C620, 6020 motor
 *@param pData original data array
 *@return mechanical angle (0~8191)
*/
s32 GetEncoderNumber(u8* pData)
{
    s32 encoder_temp;
	encoder_temp = pData[0]<<8 | pData[1];
	return encoder_temp;
}