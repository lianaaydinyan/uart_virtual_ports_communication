#ifndef _uart_
#define _uart_

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h> 

#define DEVICE "\\\\.\\COM4" // in my com0com its active and connected to COM9
#define TxBUFFER_SIZE 128 
#define RxBUFFER_SIZE 128 
#define CRC16_POLYNOMIAL 0x8005
#define data_size 64

// typedef struct {
//     bool start_bit;   
//     uint8_t data_bits;
//     bool parity_bit;
//     bool stop_bit;
//     uint16_t crc;
// }   UART_Frame;

typedef struct
{
    double      avg_speed;
    double      elapsed_time;
    uint16_t    received_data;
    uint16_t    crc_value;
    uint16_t    crc_len;
    uint16_t    data_len;
} INFO_frame;

HANDLE      openUART(const char* device);
int         configureUART(HANDLE uart_handle);
int         setUARTTimeouts(HANDLE uart_handle);
uint16_t    crc16(uint8_t *buffer, size_t length);
void        clearTxBuffer(char *TxBuffer, size_t size);
void        fillTheFrame(char *TxBuffer, INFO_frame frame);
uint16_t    crc16Ibm(const uint8_t *data, size_t length);
int         receiveData(HANDLE uart_handle, uint8_t* buffer, size_t buffer_size, INFO_frame *frame);

#endif