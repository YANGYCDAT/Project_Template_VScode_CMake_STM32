#pragma once
#include "usart.h"

#define UART1_DMA_REC_BUFFER_SIZE 50
#define UART2_DMA_REC_BUFFER_SIZE 500
#define UART3_DMA_REC_BUFFER_SIZE 500
#define UART4_DMA_REC_BUFFER_SIZE 500
#define UART5_DMA_REC_BUFFER_SIZE 500
#define UART6_DMA_REC_BUFFER_SIZE 500

extern unsigned char uart1_dma_rec_buffer[UART1_DMA_REC_BUFFER_SIZE];
extern unsigned char uart2_dma_rec_buffer[UART2_DMA_REC_BUFFER_SIZE];
extern unsigned char uart3_dma_rec_buffer[UART3_DMA_REC_BUFFER_SIZE];
extern unsigned char uart4_dma_rec_buffer[UART4_DMA_REC_BUFFER_SIZE];
extern unsigned char uart5_dma_rec_buffer[UART5_DMA_REC_BUFFER_SIZE];
extern unsigned char uart6_dma_rec_buffer[UART6_DMA_REC_BUFFER_SIZE];


int UART_Receive_DMA_No_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Size);