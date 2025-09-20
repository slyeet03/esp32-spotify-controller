#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class MyDisplay {
public:
    void begin();
    void printMessage(String msg);

private:
    Adafruit_SSD1306 display{128, 64, &Wire};
};

#endif
