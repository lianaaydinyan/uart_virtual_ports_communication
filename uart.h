#ifndef _uart_
#define _uart_

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdbool.h> 

#define DEVICE "\\\\.\\COM4" // in my com0com its active and connected to COM9
#define TxBUFFER_SIZE 8 
#define RxBUFFER_SIZE 100 
#define CRC16_POLYNOMIAL 0x8005

typedef struct {
    bool start_bit;   
    uint8_t data_bits;
    bool parity_bit;
    bool stop_bit;
    uint16_t crc;
}   UART_Frame;

HANDLE      openUART(const char* device);
int         configureUART(HANDLE uart_handle);
int         setUARTTimeouts(HANDLE uart_handle);
uint16_t    crc16(const uint8_t *data, size_t length);
uint16_t    crc16(const uint8_t *data, size_t length);
uint16_t    crc16_ibm(const uint8_t *data, size_t length);
//int         sendFrame(HANDLE uart_handle, UART_Frame frame);
UART_Frame  createUARTFrame(uint8_t data, bool use_parity, bool parity_type);
int         receiveData(HANDLE uart_handle, uint8_t* buffer, size_t buffer_size);

#endif