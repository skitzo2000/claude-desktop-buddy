// M1 skeleton — minimal main.cpp to verify the CYD toolchain builds and
// flashes. Empty setup/loop; the upstream firmware lives in
// src/main.cpp.upstream and gets ported in M2+.

#include <Arduino.h>

void setup() {
    Serial.begin(115200);
    delay(100);
    Serial.println("cyd-claudepet: M1 skeleton boot");
}

void loop() {
    delay(100);
}
