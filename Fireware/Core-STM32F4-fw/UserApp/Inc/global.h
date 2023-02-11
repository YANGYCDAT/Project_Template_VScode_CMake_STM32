#pragma once

#include "system_monitor.h"
#include "led.h"
#include "print.h"

class Global {
public:
    static SystemMonitor system_monitor;
    static Led led;
    static Print print;
};






