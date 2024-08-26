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
    uint8_t buffer[BUFFER_SIZE];
    while (true)
    {
        if (receiveData(uart_handle, buffer, BUFFER_SIZE) == 0)
        {
            frame = createUARTFrame(buffer[1], true, buffer[2]);
            if (sendFrame(uart_handle, frame) != 0)
                break;
        }
        else
            break;
    }
    CloseHandle(uart_handle);
    printf("UART device closed.\n");
    return 0;
}
