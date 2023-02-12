#include "common_inc.h"
#include "communication.h"
#include "usart.h"
#include "retarget.h"

void InitCommunication(void)
{
    RetargetInit(&huart5); // using UART5 for debug input/output
    Global::vofa.SetUartHandle(&huart4); // using UART4 for Vofa+ communication
}