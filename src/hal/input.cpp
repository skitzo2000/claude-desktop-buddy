#include "input.h"

bool InputButton::wasPressed()  { return false; }
bool InputButton::wasReleased() { return false; }
bool InputButton::isPressed()   { return false; }
bool InputButton::pressedFor(uint32_t ms) { (void)ms; return false; }

InputButton inputA;
InputButton inputB;

void inputBegin()  {}
void inputUpdate() {}
