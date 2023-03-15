#include "common_inc.h"
#include "uart_protocol.h"
#include "usart.h"


/**
 * @brief Decode the datas from the navigation computer
 *
 * @param NULL
 */
void UART_NavigationDataDecode(u8* buffer)
{
	if(	buffer[0]==0x55 && buffer[1]==0x00) {
		memcpy(&(Global::navigation.m_data_receive_frame), (u8*)buffer, 
		sizeof(Global::navigation.m_data_receive_frame));	
    }	
}



/**
 * @brief Decode the datas from the aim assist computer
 *
 * @param NULL
 */
void UART_AimAssitDataDecode(u8* buffer)
{
    
}



/**
 * @brief Decode the datas from the DJI remote controller
 *
 * @param NULL
 */
void UART_DJIRCDataDecode(unsigned char* buffer)
{
    // right rocker bar
	Global::dji_rc.channel.Ch0 = (buffer[0] | (buffer[1] << 8)) & 0x07FF;           					// Channe0——水平通道
	Global::dji_rc.channel.Ch1 = ((buffer[1]) >> 3 | (buffer[2] << 5)) & 0x07FF;   					// Channe1——垂直通道
	
	
	// left rocker bar
	Global::dji_rc.channel.Ch2 = ((buffer[3] >> 6 | (buffer[3] << 2) | (buffer[4] << 10))) & 0x07FF;	// Channe2——水平通道
	Global::dji_rc.channel.Ch3 = ((buffer[4] >> 1) | (buffer[5] << 7)) & 0x07FF;                   	// Channe3——垂直通道
	
	
	// pulley
	Global::dji_rc.channel.Ch4 = (buffer[16] | (buffer[17] << 8)) & 0x07ff;                        	// Channe4——垂直通道

	
	// left switch
	Global::dji_rc.channel.SW_L = ((buffer[5] >> 4) & 0x000C) >> 2;
	
	
	// right switch
	Global::dji_rc.channel.SW_R = ((buffer[5] >> 4) & 0x0003);

}