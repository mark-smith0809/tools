#ifndef INPUTSTATUS_H
#define INPUTSTATUS_H
#include <cstdint>

enum InputStatus : uint32_t {
    CONTINUING_NUM = 0,
    WAITING_NEW_NUM = 1,
    COMPLETE_INPUT = 2,
};

#endif // INPUTSTATUS_H
