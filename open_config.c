#include "uart.h"

HANDLE openUART(const char* device)
{
    printf("Opening UART device %s...\n", device);
    HANDLE uart_handle = CreateFile(device, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (uart_handle == INVALID_HANDLE_VALUE)
        printf("Unable to open UART. Error: %ld\n", GetLastError());
    else
        printf("UART device opened successfully.\n");
    return uart_handle;
}

int configureUART(HANDLE uart_handle)
{
    DCB dcbSerialParams = {0};
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

    if (!GetCommState(uart_handle, &dcbSerialParams))
    {
        printf("Error getting UART state. Error: %ld\n", GetLastError());
        return 1;
    }
    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;

    if (!SetCommState(uart_handle, &dcbSerialParams))
    {
        printf("Error setting UART state. Error: %ld\n", GetLastError());
        return 1;
    }
    return 0;
}

int setUARTTimeouts(HANDLE uart_handle)
{
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 150;
    timeouts.ReadTotalTimeoutConstant = 150;
    timeouts.ReadTotalTimeoutMultiplier = 30;
    timeouts.WriteTotalTimeoutConstant = 150;
    timeouts.WriteTotalTimeoutMultiplier = 30;

    if (!SetCommTimeouts(uart_handle, &timeouts))
    {
        printf("Error setting UART timeouts. Error: %ld\n", GetLastError());
        return 1;
    }
    return 0;
}
