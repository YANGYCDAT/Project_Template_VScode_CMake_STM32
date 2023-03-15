#include "common_inc.h"
#include "sentry_robot.h"
#include "can.h"
#include "m3508.h"
#include "gm6020.h"
#include "pid.h"
#include "encoder.h"


/**
*@brief Initial the whole Sentry robot
* 
*@param 
*/
void SentryRobot::Init(void)
{
    // Initial all actuators
    InitAllActuators();

    // Initial all Sensors
    InitAllSensors();
}



/**
*@brief Initial all actuators of the Sentry robot
* 
*@param 
*/
void SentryRobot::InitAllActuators(void)
{
    chassis_motor[CHASSIS_FLA_MOTOR] = new M3508(&hcan2, CHASSIS_FLA_MOTOR_ID,  CHASSIS_STEER_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_FLA_MOTOR]->m_angle_pid = new Pid(20, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_FLA_MOTOR]->m_speed_pid = new Pid(50, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_FLA_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_FLA_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);  
    
    chassis_motor[CHASSIS_FRA_MOTOR] = new M3508(&hcan2, CHASSIS_FRA_MOTOR_ID, CHASSIS_STEER_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_FRA_MOTOR]->m_angle_pid = new Pid(20, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_FRA_MOTOR]->m_speed_pid = new Pid(50, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_FRA_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_FRA_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);   
    
    chassis_motor[CHASSIS_BLA_MOTOR] = new M3508(&hcan2, CHASSIS_BLA_MOTOR_ID, CHASSIS_STEER_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_BLA_MOTOR]->m_angle_pid = new Pid(20, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_BLA_MOTOR]->m_speed_pid = new Pid(50, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_BLA_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_BLA_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);
        
    chassis_motor[CHASSIS_BRA_MOTOR] = new M3508(&hcan2, CHASSIS_BRA_MOTOR_ID, CHASSIS_STEER_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_BRA_MOTOR]->m_angle_pid = new Pid(20, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_BRA_MOTOR]->m_speed_pid = new Pid(50, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_BRA_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_BRA_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);
    
    chassis_motor[CHASSIS_FRL_MOTOR] = new M3508(&hcan1, CHASSIS_FRL_MOTOR_ID, CHASSIS_SPEED_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_FRL_MOTOR]->m_speed_pid = new Pid(120, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_FRL_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_FRL_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);   
    
    chassis_motor[CHASSIS_FLL_MOTOR] = new M3508(&hcan1, CHASSIS_FLL_MOTOR_ID, CHASSIS_SPEED_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_FLL_MOTOR]->m_speed_pid = new Pid(120, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_FLL_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_FLL_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);   
    
    chassis_motor[CHASSIS_BLL_MOTOR] = new M3508(&hcan1, CHASSIS_BLL_MOTOR_ID, CHASSIS_SPEED_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_BLL_MOTOR]->m_speed_pid = new Pid(120, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_BLL_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_BLL_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);   
    
    chassis_motor[CHASSIS_BRL_MOTOR] = new M3508(&hcan1, CHASSIS_BRL_MOTOR_ID, CHASSIS_SPEED_MOTOR_REDUCTION_RATIO);
    chassis_motor[CHASSIS_BRL_MOTOR]->m_speed_pid = new Pid(120, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    chassis_motor[CHASSIS_BRL_MOTOR]->m_encoder = new AbsEncoder(CHASSIS_BRL_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);   
    
    gimbal_motor[GIMBAL_YAW_MOTOR] = new GM6020(&hcan2, GIMBAL_YAW_MOTOR_ID, GIMBAL_MOTOR_REDUCTION_RATIO);
    gimbal_motor[GIMBAL_YAW_MOTOR]->m_angle_pid = new Pid(10, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    gimbal_motor[GIMBAL_YAW_MOTOR]->m_speed_pid = new Pid(50, 0.00, 0, 10, 20000, 20000, 5000, 2000);
    gimbal_motor[GIMBAL_YAW_MOTOR]->m_encoder = new AbsEncoder(GIMBAL_PITCH_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);

    gimbal_motor[GIMBAL_PITCH_MOTOR] = new GM6020(&hcan2, GIMBAL_PITCH_MOTOR_ID, GIMBAL_MOTOR_REDUCTION_RATIO);
    gimbal_motor[GIMBAL_PITCH_MOTOR]->m_angle_pid = new Pid(10, 0.01, 0, 10, 20000, 20000, 5000, 2000);
    gimbal_motor[GIMBAL_PITCH_MOTOR]->m_speed_pid = new Pid(30, 0.01, 0, 10, 20000, 20000, 5000, 2000);
    gimbal_motor[GIMBAL_PITCH_MOTOR]->m_encoder = new AbsEncoder(GIMBAL_YAW_ENCODER_ZERO_VALUE, ENCODER_RESOLUTION);

    // initialize the robot state
    chassis_speed_target = CHASSIS_INIT_SPEED;
    chassis_angle_target = CHASSIS_INIT_ANGLE;
    gimbal_yaw_angle_target = GIMBAL_YAW_INIT_ANGLE;
}



/**
 *@brief Initial all sensors of the Sentry robot
 * 
 *@param 
*/
void SentryRobot::InitAllSensors(void)
{

}



/**
 *@brief control the chassis to move 
 * 
 *@param 
*/
void SentryRobot::MoveChassis(void)
{
    if (chassis_mode == CHASSIS_MANNAL || chassis_mode == CHASSIS_AUTO) {
        for (int i = 0; i < 4; i++) {
            chassis_motor[i]->AngleControl();
        }
        for (int i = 4; i < CHASSIS_MOTOR_NUM; i++) {
            chassis_motor[i]->SpeedControl();
        }
    } else {
        for (int i = 0; i < CHASSIS_MOTOR_NUM; i++) {
            chassis_motor[i]->DisableControl();
        }
    }
}



/**
 *@brief control the gimbal to move
 * 
 *@param 
*/
void SentryRobot::MoveGimbal(void)
{
    if (gimbal_mode != GIMBAL_SAFE) {
        for (int i = 0; i < GIMBAL_MOTOR_NUM; i++) {
            // gimbal_motor[i]->AngleControl();
        }
    } else {
        for (int i = 0; i < GIMBAL_MOTOR_NUM; i++) {
            // gimbal_motor[i]->DisableControl();
        }
    }
}



/**
 *@brief Set the sentry robot chassis line wheel speed to the specified speed
 * 
 *@param 
*/
void SentryRobot::SetChassisSpeedTarget(float fll_motor, float bll_motor, float frl_motor, float brl_motor)
{
    chassis_motor[CHASSIS_FLL_MOTOR]->m_speed_target = fll_motor;
    chassis_motor[CHASSIS_BLL_MOTOR]->m_speed_target = bll_motor;
    chassis_motor[CHASSIS_FRL_MOTOR]->m_speed_target = frl_motor;
    chassis_motor[CHASSIS_BRL_MOTOR]->m_speed_target = brl_motor;
}



/**
 *@brief Set the sentry robot chassis steer angle to the specified angle
 * 
 *@param 
*/
void SentryRobot::SetChassisAngleTarget(float fla_steer, float bla_steer, float fra_steer, float bra_steer)
{
    chassis_motor[CHASSIS_FLA_MOTOR]->m_angle_target = fla_steer;
    chassis_motor[CHASSIS_BLA_MOTOR]->m_angle_target = bla_steer;
    chassis_motor[CHASSIS_FRA_MOTOR]->m_angle_target = fra_steer;
    chassis_motor[CHASSIS_BRA_MOTOR]->m_angle_target = bra_steer;
}