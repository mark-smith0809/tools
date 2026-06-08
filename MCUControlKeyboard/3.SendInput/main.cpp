#include "SimulateKeyBoard.h"
#include "Test.h"

#include <windows.h>

#include <iostream>
#include <thread>

int main() {
    // 设置控制台输出代码页为 UTF-8，避免中文乱码
    SetConsoleOutputCP(CP_UTF8);

    // WORD wVkCode[] = {0xa2, 0xa4, 0x41}; // ctrl + alt + a
    WORD wVkCode[] = {0x41}; // 仅模拟按下 'A' 键

    std::thread t1(TestSimulateKeyPress, wVkCode, sizeof(wVkCode) / sizeof(WORD));

    t1.join();

    return 0;
}