#pragma once
#include <stdint.h>

class InputButton {
public:
    bool wasPressed();
    bool wasReleased();
    bool isPressed();
    bool pressedFor(uint32_t ms);
};

extern InputButton inputA;
extern InputButton inputB;

void inputBegin();
void inputUpdate();
