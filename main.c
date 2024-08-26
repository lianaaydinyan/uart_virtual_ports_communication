#include "uart.h"

int main()
{
    HANDLE uart_handle = openUART(DEVICE);
    if (uart_handle == INVALID_HANDLE_VALUE)
        return 1;

    if (configureUART(uart_handle) != 0)
    {
        CloseHandle(uart_handle);
        return 1;
    }

    if (setUARTTimeouts(uart_handle) != 0)
    {
        CloseHandle(uart_handle);
        return 1;
    }

    INFO_frame info;
    char RxBuffer[RxBUFFER_SIZE] = {""};
    char TxBuffer[TxBUFFER_SIZE] = {""};
     
    while (true)
    {
        if (receiveData(uart_handle, RxBuffer, data_size, &info) == 0) 
        {
        printf("Sending packet...");
        printf("%s \n", RxBuffer);
        DWORD bytesWritten;
        fillTheFrame(TxBuffer, info);
            if (!WriteFile(uart_handle, TxBuffer, sizeof(TxBuffer), &bytesWritten, NULL))
            {
                printf("Error writing to UART. Error: %ld\n", GetLastError());
                return 1;
            }
        }
        else
            break;
    }
    CloseHandle(uart_handle);
    printf("UART device closed.\n");
    return 0;
}



