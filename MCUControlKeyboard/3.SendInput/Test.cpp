#include "Test.h"

#include <chrono>
#include <iostream>

void TestSimulateKeyPress(WORD* wVkCodes, size_t length)
{
    auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    );
    std::cout << "毫秒级时间戳: " << now_ms.count() << std::endl;
    for (int i = 0; i < 5; ++i) {
        auto temp = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        );
        auto diff = temp - now_ms;
        now_ms = temp;
        std::cout << "毫秒级时间戳: " << now_ms.count() << "diff:" << diff.count() << std::endl;
        Sleep(100); // 模拟按键之间的间隔
    }
}