#include "uart.h"

int sendFrame(HANDLE uart_handle, UART_Frame frame)
{
    uint8_t buffer[BUFFER_SIZE];
    buffer[0] = frame.start_bit;
    buffer[1] = frame.data_bits;
    buffer[2] = frame.parity_bit;
    buffer[3] = frame.stop_bit;

    printf("Sending frame...\n");
    DWORD bytesWritten;
    if (!WriteFile(uart_handle, buffer, sizeof(buffer), &bytesWritten, NULL))
    {
        printf("Error writing to UART. Error: %ld\n", GetLastError());
        return 1;
    }

    return 0;
}