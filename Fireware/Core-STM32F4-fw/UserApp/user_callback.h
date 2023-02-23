#ifndef USER_CALLBACK
#define USER_CALLBACK


#ifdef __cplusplus
extern "C" {
#endif

void User_SysTickCallback(void);
void User_UART_RX_Callback(UART_HandleTypeDef *huart);
void User_CAN_RX_Callback(CAN_HandleTypeDef *hcan);

#ifdef __cplusplus
}
#endif




#endif
