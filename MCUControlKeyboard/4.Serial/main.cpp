#include <windows.h>
#include <iostream>

int main() {
    // 设置控制台输出代码页为 UTF-8，避免中文乱码
    SetConsoleOutputCP(CP_UTF8);

    // 1. 打开串口 (如 COM3)
    HANDLE hSerial = CreateFileA("COM7",
        GENERIC_READ | GENERIC_WRITE,
        0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Failed to open COM port\n");
        return 1;
    }

    // 2. 配置串口参数 (波特率、数据位等)
    DCB dcbSerialParams = { 0 };
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    GetCommState(hSerial, &dcbSerialParams);
    dcbSerialParams.BaudRate = CBR_9600;  // 波特率 9600
    dcbSerialParams.ByteSize = 8;         // 数据位 8
    dcbSerialParams.StopBits = ONESTOPBIT;// 停止位 1
    dcbSerialParams.Parity = NOPARITY;     // 无校验
    SetCommState(hSerial, &dcbSerialParams);

    // 3. 设置超时 (防止ReadFile无限等待)
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50000;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    SetCommTimeouts(hSerial, &timeouts);

    // 4. 读取数据
    char buffer[256];
    DWORD bytesRead;
    if (ReadFile(hSerial, buffer, sizeof(buffer), &bytesRead, NULL)) {
        printf("Received %lu bytes: ", bytesRead);
        for (size_t i = 0; i < bytesRead; ++i) {
            printf("0x%02X ", static_cast<unsigned char>(buffer[i]));
        }
        printf("\n");
    } else {
        printf("Failed to read data\n");
    }

    // 5. 发送数据
    for (size_t i = 1; i < 5; ++i) { // 因为stm32演示代码使用0xff作为帧头，0xfe作为帧尾
        buffer[i] = ~buffer[i]; // 简单地取反数据作为回应
    }
    DWORD bytesWritten;
    if (WriteFile(hSerial, buffer, bytesRead, &bytesWritten, NULL)) {
        printf("Sent %lu bytes: ", bytesWritten);
        for (size_t i = 0; i < bytesWritten; ++i) {
            printf("0x%02X ", static_cast<unsigned char>(buffer[i]));
        }
        printf("\n");
    } else {
        printf("Failed to send data\n");
    }
    FlushFileBuffers(hSerial);  // 等待数据从硬件发送完成

    // 6. 关闭串口
    CloseHandle(hSerial);
    return 0;
}