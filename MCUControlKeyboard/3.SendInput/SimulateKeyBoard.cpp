#include "SimulateKeyBoard.h"

#include <iostream>

void SimulateKeyUp(WORD wVkCode) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD; // 事件类型为键盘
    input.ki.wVk = wVkCode;      // 要模拟的虚拟键码
    input.ki.dwFlags = KEYEVENTF_KEYUP; // 标记为释放事件

    UINT uSent = SendInput(1, &input, sizeof(INPUT));
    if (uSent != 1) {
        std::cerr << "模拟按键释放失败!" << std::endl;
    }
}