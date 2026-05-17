#include "board.h"
#include <SPI.h>

// Display uses the default `SPI` instance (VSPI) per build_flags pin map.
// Touch lives on a physically separate HSPI bus — TFT_eSPI's built-in
// TOUCH_CS sharing model does NOT apply on the CYD.
TFT_eSPI tft;
SPIClass hspiTouch(HSPI);
XPT2046_Touchscreen ts(33, 36);  // CS=GPIO33, IRQ=GPIO36

void boardBegin() {
    tft.init();
    tft.setRotation(0);                 // portrait, 240x320
    hspiTouch.begin(25, 39, 32);        // HSPI: SCK=25, MISO=39, MOSI=32
    ts.begin(hspiTouch);                // bind touch to HSPI (critical)
    ts.setRotation(0);
}

void boardLoop() {
    // Reserved for cooperative per-tick housekeeping (touch IRQ debounce,
    // backlight fade, etc.). Empty until M2.2/M3 modules need it.
}
