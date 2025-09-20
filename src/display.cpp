#include "display.h"
#include <Wire.h>

void MyDisplay::begin() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println("SSD1306 allocation failed");
        return;
    }
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.display();
}

void MyDisplay::printMessage(String msg) {
    display.clearDisplay();
    display.setCursor(0, 20);
    display.println(msg);
    display.display();
}
