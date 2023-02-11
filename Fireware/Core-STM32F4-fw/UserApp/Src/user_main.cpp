#include "common_inc.h"
#include "user_main.h"



/**
 * @brief user main function (user code starts here)
 *
 * @param NULL
 */
void UserMain() {
    // Initialize communnication
    InitCommunication();

    // Launch all tasks
    LaunchAllTasks();
}