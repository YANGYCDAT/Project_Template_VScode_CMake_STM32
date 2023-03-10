#pragma once
#include "m3508.h"
#include "gm6020.h"

// The encoder value corresponding to mechanical zero of the gimbal motor
#define GIMBAL_YAW_ENCODER_ZERO_VALUE ( (uint32_t) 123 )
#define GIMBAL_PITCH_ENCODER_ZERO_VALUE ( (uint32_t) 234 )

// The encoder value corresponding to mechanical zero of the chassis motor
#define CHASSIS_FLA_ENCODER_ZERO_VALUE ( (uint32_t) 345 )
#define CHASSIS_FRA_ENCODER_ZERO_VALUE ( (uint32_t) 456 )
#define CHASSIS_BLA_ENCODER_ZERO_VALUE ( (uint32_t) 567 )
#define CHASSIS_BRA_ENCODER_ZERO_VALUE ( (uint32_t) 678 )
#define CHASSIS_FLL_ENCODER_ZERO_VALUE ( (uint32_t) 789 )
#define CHASSIS_FRL_ENCODER_ZERO_VALUE ( (uint32_t) 890 )
#define CHASSIS_BLL_ENCODER_ZERO_VALUE ( (uint32_t) 901 )
#define CHASSIS_BRL_ENCODER_ZERO_VALUE ( (uint32_t) 1234 )

// The resolution of encoder
#define ENCODER_RESOLUTION ( (uint32_t) 8192)

// The reduction ratio of chassis motor
#define CHASSIS_MOTOR_REDUCTION_RATIO ( (uint32_t) 19 )

// The reduction ratio of gimbal motor
#define GIMBAL_MOTOR_REDUCTION_RATIO ( (uint32_t) 1 )

// Motor ID(same type motors should have different ID)
#define GIMBAL_YAW_MOTOR_ID ( (uint8_t) 5 )
#define GIMBAL_PITCH_MOTOR_ID ( (uint8_t) 2 )
#define CHASSIS_FLA_MOTOR_ID ( (uint8_t) 1 )
#define CHASSIS_FRA_MOTOR_ID ( (uint8_t) 2 )
#define CHASSIS_BLA_MOTOR_ID ( (uint8_t) 3 )
#define CHASSIS_BRA_MOTOR_ID ( (uint8_t) 4 )
#define CHASSIS_FLL_MOTOR_ID ( (uint8_t) 5 )
#define CHASSIS_FRL_MOTOR_ID ( (uint8_t) 6 )
#define CHASSIS_BLL_MOTOR_ID ( (uint8_t) 7 )
#define CHASSIS_BRL_MOTOR_ID ( (uint8_t) 8 )

// Motor number
#define CHASSIS_MOTOR_NUM ( (uint8_t) 8 )
#define GIMBAL_MOTOR_NUM ( (uint8_t) 2 )

// Robot Initial State
#define CHASSIS_INIT_SPEED ( (float) 0.0f )
#define CHASSIS_INIT_ANGLE ( (float) 10.0f )
#define GIMBAL_YAW_INIT_ANGLE ( (float) 20.0f )



class SentryRobot {
public:
    enum ChassisMotor {
        CHASSIS_FLA_MOTOR = 0,
        CHASSIS_FRA_MOTOR,
        CHASSIS_BLA_MOTOR,
        CHASSIS_BRA_MOTOR,
        CHASSIS_FLL_MOTOR,
        CHASSIS_FRL_MOTOR,
        CHASSIS_BLL_MOTOR,
        CHASSIS_BRL_MOTOR
    };
    M3508* chassis_motor[CHASSIS_MOTOR_NUM];
    float chassis_speed_current;
    float chassis_angle_current; 
    float chassis_speed_target;
    float chassis_angle_target; 

    enum GimbalMotor {
        GIMBAL_YAW_MOTOR = 0,
        GIMBAL_PITCH_MOTOR
    };
    GM6020* gimbal_motor[GIMBAL_MOTOR_NUM];
    float gimbal_yaw_speed_current;
    float gimbal_yaw_angle_current;
    float gimbal_yaw_speed_target;
    float gimbal_yaw_angle_target;
    float gimbal_pitch_speed_current;
    float gimbal_pitch_angle_current;
    float gimbal_pitch_speed_target;
    float gimbal_pitch_angle_target;

    void Init(void);

    void StateUpdate(void);
    void MoveChassis(void);
    void MoveGimbal(void);

    SentryRobot(){};
    ~SentryRobot(){};

private:
    void InitAllActuators(void);
    void InitAllSensors(void);
};