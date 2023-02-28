#include "common_inc.h"
#include "user_main.h"



/**
 * @brief user main function (user code starts here)
 *
 * @param NULL
 */
void UserMain() {
    // Initialize BSP
    InitCommunication();

    // Initialize sentry robot parameters
    Global::sentry.Init();

    // Launch all tasks
    LaunchAllTasks();
}