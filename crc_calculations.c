#include "uart.h"

uint16_t crc16(const uint8_t *data, size_t length)
{
    uint16_t crc = 0xFFFF; // crc register can be 0x0000 , 0xFFFF , 0x1DOF
    for (size_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)data[i] << 8;
        for (int j = 0; j < 8; j++)
        {
            if ((crc & 0x8000) == 1) // mbs
                crc = (crc << 1) ^ 0x1021;
            else
                crc <<= 1;
        }
    }
    return crc;
}

uint16_t crc16Ibm(const uint8_t *data, size_t length)
{
    uint16_t crc = 0x0000;
    for (size_t i = 0; i < length; i++)
    {
        crc ^= (uint16_t)data[i]; 
        for (int j = 0; j < 8; j++)
        {
            if ((crc & 0x0001) == 0) // lbs 
                crc >>= 1;
            else
                crc = (crc >> 1) ^ CRC16_POLYNOMIAL;
        }
    }
    return crc;
}
