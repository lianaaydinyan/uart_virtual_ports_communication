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

    UART_Frame frame;
    char RxBuffer[RxBUFFER_SIZE];
    char TxBuffer[TxBUFFER_SIZE] = {""};
     
    while (true)
    {
        if (receiveData(uart_handle, RxBuffer, RxBUFFER_SIZE) == 0) 
        {
        printf("Sending frame...");
        printf("%s \n", RxBuffer);
        DWORD bytesWritten;
        if (!WriteFile(uart_handle, TxBuffer, sizeof(TxBuffer) - 1, &bytesWritten, NULL))
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
