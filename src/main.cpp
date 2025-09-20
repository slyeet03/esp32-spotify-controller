#include <Arduino.h>
#include <WiFi.h>
#include "secrets.h"
#include "display.h"
#include "potentiometer.h"

// Objects
MyDisplay myDisplay;
MyPot myPot(34);

// Messages
String messages[] = {"Hello", "World", "ESP32", "Music"};
int msgIndex = -1;

// Wi-Fi
const char* WIFI_SSID = "";
const char* WIFI_PASS = "";
bool wifiConnected = false;

void setup() {
    Serial.begin(115200);

    // Initialize modules
    myDisplay.begin();
    Serial.println("OLED initialized");

    // Connect Wi-Fi non-blocking
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Connecting to WiFi...");
}

void loop() {
    // Wi-Fi handling
    if (!wifiConnected && WiFi.status() == WL_CONNECTED) {
        wifiConnected = true;
        Serial.println("\nConnected to WiFi!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
    } else if (!wifiConnected){ 
        Serial.print(".");
    }

    // Potentiometer -> Display
    int val = myPot.read();
    int index = map(val, 0, 4095, 0, 3);

    if (index != msgIndex) {
        msgIndex = index;
        myDisplay.printMessage(messages[msgIndex]);
        Serial.print("Showing message: ");
        Serial.println(messages[msgIndex]);
    }

    delay(100);
}
