#include "can_interface.h"
#include "common_inc.h"

CANContext can1_context;
CANContext can2_context;



/**
 * @brief Init the CAN
 *
 * @param CAN_HandleTypeDef* hcan
 */
void CANContext::Init(CAN_HandleTypeDef* hcan, uint32_t id_type, uint32_t frame_type, uint32_t length)
{
    handle = hcan;
    tx_header.IDE = id_type;
    tx_header.RTR = frame_type; 
    tx_header.DLC = length;
}


/**
 * @brief Configure the Filter for CAN
 *
 * @param CAN_HandleTypeDef* hcan
 */
void CAN_Filter_Config(CAN_HandleTypeDef* hcan, uint32_t filter_id)
{ 
  CAN_FilterTypeDef  sFilterConfig; 
  sFilterConfig.FilterBank = filter_id; // Specify Filter ID
  sFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; // MASK Mode   
  sFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; // 32 bit MASK 
  sFilterConfig.FilterIdHigh = 0x000;  // Specify device ID high 16 bits
  sFilterConfig.FilterIdLow = 0x0000; // Specify device ID low 16 bits
  sFilterConfig.FilterMaskIdHigh = 0x0000; // Specify MASK high 16 bits
  sFilterConfig.FilterMaskIdLow = 0x0000; // Specify MASK low 16 bits
  sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0; // Use fifo0 to store dates and trigger interruption
  sFilterConfig.FilterActivation = ENABLE; // Enable filter 
  if (HAL_CAN_ConfigFilter(hcan, &sFilterConfig) != HAL_OK) 
  { 
    Error_Handler(); 
  } 
}


/**
 * @brief Use can to send messages
 *
 * @param CAN_HandleTypeDef* hcan
 */
void CanSendMessage(CANContext *p_message)
{
  HAL_CAN_AddTxMessage(p_message->handle, &(p_message->tx_header), &(p_message->tx_data[0]), &(p_message->last_mailbos));
}



/**
 * @brief Get the message corresponding to CAN
 *
 * @param CAN_HandleTypeDef* hcan
 */
CANContext* GetCANContext(CAN_HandleTypeDef* hcan)
{
    if (hcan->Instance == CAN1)
        return &can1_context;
    else if (hcan->Instance == CAN2)
        return &can2_context;
    else
        return nullptr;
}