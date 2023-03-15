#pragma once

#include "system_monitor.h"
#include "led.h"
#include "vofa.h"
#include "navigation.h"
#include "djirc.h"
#include "sentry_robot.h"
#include "can_interface.h"

#define CHASSIS_DEBUG
// #define NAVIGATION_DEBUG

class Global {
public:
    // instance
    static SystemMonitor system_monitor;
    static Led led;
    static Vofa vofa;
    static SentryRobot sentry;
    static Navigation navigation;
    static DJIRC dji_rc;

    // states
    enum ControlMode {
        SAFE = 0,
        CALIBRATE,
        RC_GS,
        AUTO_G_RC_S,
        AUTO_GS_RC_C,
        AUTO_CGS,
        RC_CG,
        AUTO_G_RC_C
    };
    static ControlMode control_mode; 

    static void ControlModeUpdate(void);
    static void RobotStatesUpdate(void);
    static void RobotTargetsUpdate(void);
};







