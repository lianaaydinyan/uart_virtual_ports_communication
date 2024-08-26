#include "uart.h"

UART_Frame createUARTFrame(uint8_t data, bool use_parity, bool parity_type)
{
    UART_Frame frame;
    frame.start_bit = true;
    frame.data_bits = data;
    if (use_parity)
        frame.parity_bit = parity_type;
    else
        frame.parity_bit = false;
    frame.stop_bit = true;
    uint8_t crc_data[3] = {frame.start_bit, frame.data_bits, frame.parity_bit};
    frame.crc = crc16(crc_data, sizeof(crc_data));
    return frame;
}
