#include "uart.h"

void fillTheFrame(char *TxBuffer, INFO_frame frame)
{
    snprintf(TxBuffer, TxBUFFER_SIZE, 
             "\nPacket info -> CRC16:0x%04X\n, Elapsed Time:%.2f\n, Average Speed:%.2f\n", 
             frame.crc_value, 
             frame.elapsed_time, 
             frame.avg_speed);
}
