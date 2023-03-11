#include "common_inc.h"
#include "user_global.h"

SystemMonitor Global::system_monitor;
Led Global::led;
Vofa Global::vofa;
SentryRobot Global::sentry;
Navigation Global::navigation;
DJIRC Global::dji_rc;

Global::ControlMode Global::control_mode;



/**
 *@brief update system control mode
 * 
 *@param 
*/
void Global::ControlModeUpdate(void) {
    // Control mode update
    if(Global::dji_rc.channel.SW_L == RC_SW_DOWN 
    && Global::dji_rc.channel.SW_R == RC_SW_DOWN) {
		Global::control_mode = Global::SAFE;
	} else if (Global::dji_rc.channel.SW_L == RC_SW_DOWN 
    && Global::dji_rc.channel.SW_R == RC_SW_MID) {
        Global::control_mode = Global::RC_GS;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_DOWN 
    && Global::dji_rc.channel.SW_R == RC_SW_UP) {
        Global::control_mode = Global::AUTO_G_RC_S;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_MID 
    && Global::dji_rc.channel.SW_R == RC_SW_UP) {
        Global::control_mode = Global::AUTO_GS_RC_C;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_UP 
    && Global::dji_rc.channel.SW_R == RC_SW_UP) {
        Global::control_mode = Global::AUTO_CGS;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_MID 
    && Global::dji_rc.channel.SW_R == RC_SW_DOWN) {
        Global::control_mode = Global::RC_CG;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_UP 
    && Global::dji_rc.channel.SW_R == RC_SW_DOWN) {
        Global::control_mode = Global::AUTO_G_RC_C;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_MID 
    && Global::dji_rc.channel.SW_R == RC_SW_MID) {
        Global::control_mode = Global::CALIBRATE;
    } else {
        Global::control_mode = Global::SAFE;
    } 

    // Set sentry robot gimbal mode 
    if (Global::control_mode == Global::AUTO_G_RC_S 
    || Global::control_mode == Global::AUTO_CGS 
    || Global::control_mode == AUTO_CGS 
    || Global::control_mode == Global::AUTO_G_RC_C) {
        Global::sentry.SetGimbalMode(SentryRobot::GIMBAL_AUTO);
    } else if (Global::control_mode == Global::RC_GS 
    || Global::control_mode == Global::Global::RC_CG) {
        Global::sentry.SetGimbalMode(SentryRobot::GIMBAL_MANNAL);
    } else {
        Global::sentry.SetGimbalMode(SentryRobot::GIMBAL_SAFE);
    }

    // Set sentry robot shoot mode
    if (Global::control_mode == Global::AUTO_GS_RC_C 
    || Global::control_mode == Global::AUTO_GS_RC_C) {
        Global::sentry.SetShootMode(SentryRobot::SHOOT_AUTO);
    } else if (Global::control_mode == Global::RC_GS 
    || Global::control_mode == Global::AUTO_G_RC_S) {
        Global::sentry.SetShootMode(SentryRobot::SHOOT_MANNAL);
    } else {
        Global::sentry.SetShootMode(SentryRobot::SHOOT_SAFE);
    }

    // Set sentry robot chassis mode
    if (Global::control_mode == Global::AUTO_CGS) {
        Global::sentry.SetChassisMode(SentryRobot::CHASSIS_AUTO);
    } else if (Global::control_mode == Global::AUTO_GS_RC_C 
    || Global::control_mode == Global::RC_CG 
    || Global::control_mode == Global::AUTO_G_RC_C) {
        Global::sentry.SetChassisMode(SentryRobot::CHASSIS_MANNAL);
    } else if (Global::control_mode == Global::CALIBRATE) {
        Global::sentry.SetChassisMode(SentryRobot::CHASSIS_CALIBRATE);
    } else {
        Global::sentry.SetChassisMode(SentryRobot::CHASSIS_SAFE);
    }
};



/**
 *@brief update the state of the sentry robot
 * 
 *@param 
*/
void Global::RobotStatesUpdate(void)
{
    // Update sentry robot current chassis state
    Global::sentry.SetChassisAngleCurrent(
        Global::sentry.chassis_motor[SentryRobot::CHASSIS_FRA_MOTOR]->m_angle_current);
    Global::sentry.SetChassisSpeedCurrent(
        Global::sentry.chassis_motor[SentryRobot::CHASSIS_FLL_MOTOR]->m_speed_current);

    // Update sentry robot current gimbal state
    Global::sentry.SetGimbalYawSpeedCurrent(
        Global::sentry.gimbal_motor[SentryRobot::GIMBAL_YAW_MOTOR]->m_speed_current);
    Global::sentry.SetGimbalYawAngleCurrent(
        Global::sentry.gimbal_motor[SentryRobot::GIMBAL_YAW_MOTOR]->m_angle_current);
    Global::sentry.SetGimbalPitchSpeedCurrent(
        Global::sentry.gimbal_motor[SentryRobot::GIMBAL_PITCH_MOTOR]->m_speed_current);
    Global::sentry.SetGimbalPitchAngleCurrent(
        Global::sentry.gimbal_motor[SentryRobot::GIMBAL_PITCH_MOTOR]->m_angle_current);
}



/**
 *@brief update the robot targets 
 * 
 *@param 
*/
void Global::RobotTargetsUpdate(void) {
    if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_MANNAL) {
        // contorlled by the remote controller
        float chassis_speed = ((float)(Global::dji_rc.channel.Ch3 - RC_CH_VALUE_OFFSET)
        / RC_CH_VALUE_RANGE * CHASSIS_SPEED_MAX);
        float chassis_angle = ((float)(Global::dji_rc.channel.Ch2 - RC_CH_VALUE_OFFSET)
        / RC_CH_VALUE_RANGE * 10);
        Global::sentry.SetChassisAngleTarget(chassis_angle);
        Global::sentry.SetChassisSpeedTarget(chassis_speed);
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_AUTO) {
        
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_CALIBRATE) {
        
    } else {
        // set the same value of the feedback to the target
        float chassis_speed = Global::sentry.chassis_speed_current;
        float chassis_angle = Global::sentry.chassis_angle_current;
        Global::sentry.SetChassisAngleTarget(chassis_angle);
        Global::sentry.SetChassisSpeedTarget(chassis_speed);
    }
}