#include "uart.h"

void fillTheFrame(char *TxBuffer, INFO_frame frame)
{
    snprintf(TxBuffer, TxBUFFER_SIZE, 
             "\nPacket info -> CRC16:0x%04X\n, Average Speed:%.2f\n, Received %d bytes of data\n",  
             frame.crc_value, 
             frame.avg_speed,
             frame.data_len);
}

void clearTxBuffer(char *TxBuffer, size_t size)
{
    memset(TxBuffer, 0, size);
}
