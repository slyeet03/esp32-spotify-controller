#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

class MyPot {
public:
    MyPot(int pin);
    int read();

private:
    int _pin;
};

#endif
