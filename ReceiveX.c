#include "uart.h"

int receiveData(HANDLE uart_handle, uint8_t* buffer, size_t buffer_size)
{
    DWORD bytesRead;
    struct timeval start_time, end_time;

    gettimeofday(&start_time, NULL);
    printf("Waiting for data...\n");

    size_t totalBytesRead = 0;
   while (totalBytesRead < 1) {
        if (ReadFile(uart_handle, buffer + totalBytesRead, buffer_size - totalBytesRead, &bytesRead, NULL))
        {
            if (bytesRead > 0)
            {
                totalBytesRead += bytesRead;
                printf("Received %lu bytes of data.\n", bytesRead);
            }
        }
        else if (totalBytesRead == 0)
        {
            printf("Error reading from UART. data : %s\n", totalBytesRead );
            return 1;     
        }
        else
        {
            printf("Error reading from UART. Error: %ld\n", GetLastError());
            return 1;
        }
   }

    gettimeofday(&end_time, NULL);
    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    printf("Elapsed time: %.6f seconds.\n", elapsed_time);

    double avg_speed = totalBytesRead / elapsed_time;
    printf("Average transfer speed: %.2f Bps.\n", avg_speed);
    uint16_t crc = crc16(buffer, totalBytesRead);
    printf("CRC16 value: 0x%04X.\n", crc);

    return 0;
}