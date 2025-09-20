#include "potentiometer.h"

MyPot::MyPot(int pin) : _pin(pin) {
    pinMode(_pin, INPUT);
}

int MyPot::read() {
    return analogRead(_pin);
}
