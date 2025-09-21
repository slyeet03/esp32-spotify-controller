#include <display.h>

void MyDisplay::begin() {
    display.init();
    display.flipScreenVertically();
    display.setFont(ArialMT_Plain_16);
    display.clear();
    display.display();
    Serial.println("SSD1306 display initialized");
}

void MyDisplay::printMessage(String msg) {
    display.clear();
    display.setTextAlignment(TEXT_ALIGN_CENTER);
    display.drawString(64, 24, msg);  // Center of 128x64 screen
    display.display();
}