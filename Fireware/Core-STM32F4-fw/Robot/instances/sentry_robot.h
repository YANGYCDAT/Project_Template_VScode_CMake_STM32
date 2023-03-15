#pragma once
#include "m3508.h"
#include "gm6020.h"

// The encoder value corresponding to mechanical zero of the gimbal motor
#define GIMBAL_YAW_ENCODER_ZERO_VALUE ( (uint32_t) 123 )
#define GIMBAL_PITCH_ENCODER_ZERO_VALUE ( (uint32_t) 234 )

// The encoder value corresponding to mechanical zero of the chassis motor
#define CHASSIS_FRA_ENCODER_ZERO_VALUE ( (uint32_t) 1321 )
#define CHASSIS_FLA_ENCODER_ZERO_VALUE ( (uint32_t) 3713)
#define CHASSIS_BLA_ENCODER_ZERO_VALUE ( (uint32_t) 4974 )
#define CHASSIS_BRA_ENCODER_ZERO_VALUE ( (uint32_t) 4117 )
#define CHASSIS_FLL_ENCODER_ZERO_VALUE ( (uint32_t) 789 )
#define CHASSIS_FRL_ENCODER_ZERO_VALUE ( (uint32_t) 890 )
#define CHASSIS_BLL_ENCODER_ZERO_VALUE ( (uint32_t) 901 )
#define CHASSIS_BRL_ENCODER_ZERO_VALUE ( (uint32_t) 1234 )

// The resolution of encoder
#define ENCODER_RESOLUTION ( (uint32_t) 8192)

// The reduction ratio of chassis motor
#define CHASSIS_STEER_MOTOR_REDUCTION_RATIO ( (uint32_t) 8 )
#define CHASSIS_SPEED_MOTOR_REDUCTION_RATIO ( (uint32_t) 19 )

// The reduction ratio of gimbal motor
#define GIMBAL_MOTOR_REDUCTION_RATIO ( (uint32_t) 1 )

// Motor ID(same type motors should have different ID)
#define GIMBAL_YAW_MOTOR_ID ( (uint8_t) 5 )
#define GIMBAL_PITCH_MOTOR_ID ( (uint8_t) 2 )
#define CHASSIS_FRA_MOTOR_ID ( (uint8_t) 1 )
#define CHASSIS_FLA_MOTOR_ID ( (uint8_t) 2 )
#define CHASSIS_BLA_MOTOR_ID ( (uint8_t) 3 )
#define CHASSIS_BRA_MOTOR_ID ( (uint8_t) 4 )
#define CHASSIS_FRL_MOTOR_ID ( (uint8_t) 1 )
#define CHASSIS_FLL_MOTOR_ID ( (uint8_t) 2 )
#define CHASSIS_BLL_MOTOR_ID ( (uint8_t) 3 )
#define CHASSIS_BRL_MOTOR_ID ( (uint8_t) 4 )

// Motor number
#define CHASSIS_MOTOR_NUM ( (uint8_t) 8 )
#define GIMBAL_MOTOR_NUM ( (uint8_t) 2 )

// Robot Initial State
#define CHASSIS_INIT_SPEED ( (float) 0.0f )
#define CHASSIS_INIT_ANGLE ( (float) 0.0f )
#define CHASSIS_CALIBRATE_ENCODE_RANGE ( (uint32_t) 200 )
#define GIMBAL_YAW_INIT_ANGLE ( (float) 20.0f )

// Robot mannal control sensitivity
#define CHASSIS_SPEED_MANNAL_CONTROL_SENSITIVITY            ( (float) 100.0f )
#define CHASSIS_ANGLE_MANNAL_CONTROL_SENSITIVITY            ( (float) 100.0f )
#define GIMBAL_PITCH_ANGLE_MANNAL_CONTROL_SENSITIVITY       ( (float) 100.0f )
#define GIMBAL_YAW_ANGLE_MANNAL_CONTROL_SENSITIVITY         ( (float) 100.0f )

// Chassis driving mode
#define CHASSIS_STEER_DRIVING_MODE
// #define CHASSIS_DIFFERENTIAL_DRIVING_MODE            
// #define CHASSIS_COMMOM_DRIVING_MODE                                    

#ifdef CHASSIS_STEER_DRIVING_MODE
#define CHASSIS_STEER_ANGLE_MAX                             ( (float)(90) )
#define CHASSIS_LINE_SPEED_MAX                              ( (float)(10) )
#endif

#ifdef CHASSIS_DIFFERENTIAL_DRIVING_MODE
#define CHASSIS_ANGLE_SPEED_MAX                              ( (float)(300) )
#define CHASSIS_LINE_SPEED_MAX                               ( (float)(20) )
#endif

#define CHASSIS_HALF_WHEEL_TREAD                            ( (float)(0.4f) )

#define CHASSIS_WHEEL_RADIUS                                (float)(0.06f)

#define RADIAN2DEGREE_VALUE                                (float)(57.29577f)


class SentryRobot {
public:
    enum ChassisMode {
        CHASSIS_SAFE = 0,
        CHASSIS_CALIBRATE,
        CHASSIS_MANNAL,
        CHASSIS_AUTO
    };
    ChassisMode chassis_mode;

    enum GimbalMode {
        GIMBAL_SAFE = 0,
        GIMBAL_MANNAL,
        GIMBAL_AUTO
    };
    GimbalMode gimbal_mode;

    enum ShootMode {
        SHOOT_SAFE = 0,
        SHOOT_MANNAL,
        SHOOT_AUTO
    };
    ShootMode shoot_mode;

    enum ChassisMotor {
        CHASSIS_FRA_MOTOR = 0,
        CHASSIS_FLA_MOTOR,
        CHASSIS_BLA_MOTOR,
        CHASSIS_BRA_MOTOR,
        CHASSIS_FRL_MOTOR,
        CHASSIS_FLL_MOTOR,
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

    void MoveChassis(void);
    void MoveGimbal(void);
    void SetChassisSpeedTarget(float fll_motor, float frl_motor, float bll_motor, float brl_motor);
    void SetChassisAngleTarget(float fla_steer, float fra_steer, float bla_steer, float bra_steer);
    inline void SetChassisMode(ChassisMode mode) {chassis_mode = mode;};
    inline void SetGimbalMode(GimbalMode mode) {gimbal_mode = mode;};
    inline void SetShootMode(ShootMode mode) {shoot_mode = mode;};
    inline void SetGimbalPitchSpeedTarget(float target) {gimbal_pitch_speed_target = target;};
    inline void SetGimbalPitchAngleTarget(float target) {gimbal_pitch_angle_target = target;};
    inline void SetGimbalYawSpeedTarget(float target) {gimbal_yaw_speed_target = target;};
    inline void SetGimbalYawAngleTarget(float target) {gimbal_yaw_angle_target = target;};
    inline void StepChassisSpeedTarget(float step) {chassis_speed_target += step;};
    inline void StepChassisAngleTarget(float step) {chassis_angle_target += step;};
    inline void StepGimbalPitchSpeedTarget(float step) {gimbal_pitch_speed_target += step;};
    inline void StepGimbalPitchAngleTarget(float step) {gimbal_pitch_angle_target += step;};
    inline void StepGimbalYawSpeedTarget(float step) {gimbal_yaw_speed_target += step;};
    inline void StepGimbalYawAngleTarget(float step) {gimbal_yaw_angle_target += step;};
    inline void SetChassisSpeedCurrent(float current) {chassis_speed_current = current;};
    inline void SetChassisAngleCurrent(float current) {chassis_angle_current = current;};
    inline void SetGimbalPitchAngleCurrent(float current) {gimbal_pitch_angle_current = current;};
    inline void SetGimbalPitchSpeedCurrent(float current) {gimbal_pitch_speed_current = current;};
    inline void SetGimbalYawAngleCurrent(float current) {gimbal_yaw_angle_current = current;};
    inline void SetGimbalYawSpeedCurrent(float current) {gimbal_yaw_speed_current = current;};


    SentryRobot(){};
    ~SentryRobot(){};

private:
    void InitAllActuators(void);
    void InitAllSensors(void);
};