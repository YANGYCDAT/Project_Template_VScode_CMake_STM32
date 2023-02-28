#pragma once

#define UART3_DMA_REC_BUFFER_SIZE 500
#define UART4_DMA_REC_BUFFER_SIZE 500
#define UART5_DMA_REC_BUFFER_SIZE 500

extern unsigned char uart3_dma_rec_buffer[UART3_DMA_REC_BUFFER_SIZE];
extern unsigned char uart4_dma_rec_buffer[UART4_DMA_REC_BUFFER_SIZE];
extern unsigned char uart5_dma_rec_buffer[UART5_DMA_REC_BUFFER_SIZE];