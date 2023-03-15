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
    && Global::dji_rc.channel.SW_R == RC_SW_MID) {
        Global::control_mode = Global::RC_C;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_UP 
    && Global::dji_rc.channel.SW_R == RC_SW_DOWN) {
        Global::control_mode = Global::AUTO_G_RC_C;
    } else if (Global::dji_rc.channel.SW_L == RC_SW_MID 
    && Global::dji_rc.channel.SW_R == RC_SW_DOWN) {
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
    } else if (Global::control_mode == Global::RC_GS) {
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
    || Global::control_mode == Global::RC_C 
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
#ifdef CHASSIS_STEER_DRIVING_MODE
    static float chassis_steer_pre = 0;
    static float chassis_steer_sum = 0;
    float steer_angle_step = 0;
    float chassis_speed = 0;
    float chassis_steer = 0;

    if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_MANNAL) {
        if (abs(Global::dji_rc.channel.Ch1 - RC_CH_VALUE_OFFSET) > RC_CH_VALUE_DEAD) {
            chassis_speed = ((float)(Global::dji_rc.channel.Ch1 - RC_CH_VALUE_OFFSET)
            / RC_CH_VALUE_RANGE * CHASSIS_LINE_SPEED_MAX / CHASSIS_WHEEL_RADIUS);
        }

        if (abs(Global::dji_rc.channel.Ch2 - RC_CH_VALUE_OFFSET) > RC_CH_VALUE_DEAD) {
            steer_angle_step = -((float)(Global::dji_rc.channel.Ch2 - RC_CH_VALUE_OFFSET)
            / RC_CH_VALUE_RANGE * CHASSIS_STEER_ANGLE_SENSITIVITY);
        }
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_AUTO) {
        chassis_steer = Global::navigation.m_data_receive_frame.m_data[0];
        chassis_speed = Global::navigation.m_data_receive_frame.m_data[1];
        chassis_steer = chassis_steer * RADIAN2DEGREE_VALUE;

        // speed max limit
        if (chassis_speed > CHASSIS_LINE_SPEED_MAX) {
            chassis_speed = CHASSIS_LINE_SPEED_MAX;
        } 
        chassis_speed = chassis_speed / CHASSIS_WHEEL_RADIUS;

        // angle max limit
        steer_angle_step = chassis_steer - chassis_steer_pre;
        chassis_steer_pre = chassis_steer;
        if (steer_angle_step > CHASSIS_STEER_ANGLE_MAX) {
            steer_angle_step = steer_angle_step - 4 * CHASSIS_STEER_ANGLE_MAX;
        } else if (steer_angle_step < -CHASSIS_STEER_ANGLE_MAX) {
            steer_angle_step = steer_angle_step + 4 * CHASSIS_STEER_ANGLE_MAX;
        }
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_CALIBRATE) {
        for (int i = 0; i < CHASSIS_MOTOR_NUM; i++) {
            Global::sentry.chassis_motor[i]->m_encoder->m_sum_value 
            = Global::sentry.chassis_motor[i]->m_encoder->m_raw_value;

            Global::sentry.chassis_motor[i]->m_encoder->m_zero_value 
            = Global::sentry.chassis_motor[i]->m_encoder->m_raw_value;
        }
        chassis_steer_pre = 0;
        chassis_steer_sum = 0;
    } else {
        chassis_steer_pre = 0;
        chassis_steer_sum = 0;
        for (int i = 0; i < 4; i++) {
            Global::sentry.chassis_motor[i]->m_td->m_aim = Global::sentry.chassis_motor[i]->m_angle_target;
            Global::sentry.chassis_motor[i]->m_td->m_x1 = Global::sentry.chassis_motor[i]->m_angle_target;
            Global::sentry.chassis_motor[i]->m_td->m_x2 = 0;
        }
    }

    chassis_steer_sum += steer_angle_step;
    
    Global::sentry.SetChassisSpeedTarget(chassis_speed, chassis_speed, -chassis_speed, -chassis_speed);
    Global::sentry.SetChassisAngleTarget(chassis_steer_sum, chassis_steer_sum, chassis_steer_sum, chassis_steer_sum);


#elif defined CHASSIS_DIFFERENTIAL_DRIVING_MODE
    if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_MANNAL) {
        // contorlled by the remote controller
        float chassis_line_speed = 0;
        float chassis_angle_speed = 0;
        if (abs(Global::dji_rc.channel.Ch3 - RC_CH_VALUE_OFFSET) > RC_CH_VALUE_DEAD) {
            chassis_line_speed = ((float)(Global::dji_rc.channel.Ch3 - RC_CH_VALUE_OFFSET)
            / RC_CH_VALUE_RANGE * CHASSIS_LINE_SPEED_MAX / CHASSIS_WHEEL_RADIUS);
        }
        if (abs(Global::dji_rc.channel.Ch2 - RC_CH_VALUE_OFFSET) > RC_CH_VALUE_DEAD) {
            chassis_angle_speed = -((float)(Global::dji_rc.channel.Ch2 - RC_CH_VALUE_OFFSET)
            / RC_CH_VALUE_RANGE * CHASSIS_ANGLE_SPEED_MAX);
        }
        
        float left_speed = chassis_line_speed - CHASSIS_HALF_WHEEL_TREAD * chassis_angle_speed;
        float right_speed = chassis_line_speed + CHASSIS_HALF_WHEEL_TREAD * chassis_angle_speed;

        Global::sentry.SetChassisSpeedTarget(left_speed, left_speed, -right_speed, -right_speed);
        Global::sentry.SetChassisAngleTarget(0, 0, 0, 0);
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_AUTO) {
        float left_speed = Global::navigation.m_data_receive_frame.m_data[0];
        float right_speed = Global::navigation.m_data_receive_frame.m_data[1];
        if (left_speed > CHASSIS_LINE_SPEED_MAX) {
            left_speed = CHASSIS_LINE_SPEED_MAX;
        } else if (left_speed < -CHASSIS_LINE_SPEED_MAX) {
            left_speed = -CHASSIS_LINE_SPEED_MAX;
        } 
        if (left_speed > CHASSIS_LINE_SPEED_MAX) {
            right_speed = CHASSIS_LINE_SPEED_MAX;
        } else if (left_speed < -CHASSIS_LINE_SPEED_MAX) {
            right_speed = -CHASSIS_LINE_SPEED_MAX;
        }
        left_speed = left_speed / CHASSIS_WHEEL_RADIUS;
        right_speed = right_speed / CHASSIS_WHEEL_RADIUS;

        Global::sentry.SetChassisSpeedTarget(left_speed, left_speed, -right_speed, -right_speed);
        Global::sentry.SetChassisAngleTarget(0, 0, 0, 0);
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_CALIBRATE) {
        for (int i = 0; i < CHASSIS_MOTOR_NUM; i++) {
            Global::sentry.chassis_motor[i]->m_encoder->m_sum_value 
            = Global::sentry.chassis_motor[i]->m_encoder->m_raw_value;

            Global::sentry.chassis_motor[i]->m_encoder->m_zero_value 
            = Global::sentry.chassis_motor[i]->m_encoder->m_raw_value;
        }
    } else {
        Global::sentry.SetChassisAngleTarget(0, 0, 0, 0);
        Global::sentry.SetChassisSpeedTarget(0, 0, 0, 0);
    }

#elif defined CHASSIS_COMMOM_DRIVING_MODE
    float chassis_angle_speed = 0;
    float chassis_line_steer = 0;

    if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_MANNAL) {
        if (abs(Global::dji_rc.channel.Ch3 - RC_CH_VALUE_OFFSET) > RC_CH_VALUE_DEAD) {

        }
        if (abs(Global::dji_rc.channel.Ch2 - RC_CH_VALUE_OFFSET) > RC_CH_VALUE_DEAD) {

        }
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_AUTO) {
        chassis_angle_speed = Global::navigation.m_data_receive_frame.m_data[0];
        chassis_line_steer = Global::navigation.m_data_receive_frame.m_data[1];
        // chassis_angle_speed = chassis_angle_speed * RADIAN2DEGREE_VALUE;
        chassis_angle_speed = chassis_angle_speed;


        // speed max limit
        if (chassis_line_steer > CHASSIS_LINE_SPEED_MAX) {
            chassis_line_steer = CHASSIS_LINE_SPEED_MAX;
        } 
        if (chassis_angle_speed > CHASSIS_ANGLE_SPEED_MAX) {
            chassis_angle_speed = CHASSIS_ANGLE_SPEED_MAX;
        } 
        chassis_line_steer = chassis_line_steer / CHASSIS_WHEEL_RADIUS;
    } else if (Global::sentry.chassis_mode == SentryRobot::CHASSIS_CALIBRATE) {
        for (int i = 0; i < CHASSIS_MOTOR_NUM; i++) {
            Global::sentry.chassis_motor[i]->m_encoder->m_sum_value 
            = Global::sentry.chassis_motor[i]->m_encoder->m_raw_value;

            Global::sentry.chassis_motor[i]->m_encoder->m_zero_value 
            = Global::sentry.chassis_motor[i]->m_encoder->m_raw_value;
        }
    } else {

    }

    Global::sentry.SetChassisSpeedTarget(chassis_line_steer, chassis_line_steer, -chassis_line_steer, -chassis_line_steer);
    Global::sentry.SetChassisAngleSpeedTarget(chassis_angle_speed, chassis_angle_speed, chassis_angle_speed, chassis_angle_speed);

#endif
}