#pragma once

#include "system_monitor.h"
#include "led.h"
#include "vofa.h"
#include "sentry_robot.h"
#include "can_interface.h"



class Global {
public:
    static SystemMonitor system_monitor;
    static Led led;
    static Vofa vofa;
    static SentryRobot sentry;
};






