#include <Arduino.h>
#include <WiFi.h>
#include "BluetoothSerial.h"
#include <display.h>
#include <potentiometer.h>

// Objects
MyDisplay myDisplay;
MyPot myPot(34);
BluetoothSerial SerialBT;

// Messages
String messages[] = {"it", "works"};
int msgIndex = -1;

// WiFi credentials - your actual credentials
const char* WIFI_SSID = "iPhone Sly";
const char* WIFI_PASS = "slyeet032005";

bool wifiConnected = false;
bool bluetoothConnected = false;

// Simple WiFi connection with 5 attempts
bool connectWiFi() {
    Serial.println("Connecting to WiFi...");
    Serial.print("SSID: ");
    Serial.println(WIFI_SSID);
    
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 5) {
        attempts++;
        Serial.print("Attempt ");
        Serial.print(attempts);
        Serial.print("/5: ");
        
        // Wait up to 10 seconds per attempt
        for (int i = 0; i < 20; i++) {
            delay(500);
            Serial.print(".");
            if (WiFi.status() == WL_CONNECTED) break;
        }
        Serial.println();
        
        if (WiFi.status() != WL_CONNECTED && attempts < 5) {
            Serial.println("Failed, retrying...");
            WiFi.disconnect();
            delay(1000);
            WiFi.begin(WIFI_SSID, WIFI_PASS);
        }
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("WiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());
        return true;
    } else {
        Serial.println("Could not connect to WiFi after 5 attempts");
        Serial.println("Continuing without WiFi...");
        return false;
    }
}

void setup() {
    Serial.begin(115200);
    
    // Initialize display
    myDisplay.begin();
    Serial.println("OLED initialized");
    myDisplay.printMessage("Starting...");
    
    // Try to connect to WiFi
    wifiConnected = connectWiFi();
    
    // Start Bluetooth
    if (SerialBT.begin("ESP32-Music-Display")) {
        Serial.println("Bluetooth started: ESP32-Music-Display");
        Serial.println("Device can be paired now!");
    } else {
        Serial.println("Bluetooth failed to start");
    }
    
    // Update display based on status
    if (wifiConnected) {
        myDisplay.printMessage("WiFi + BT Ready");
    } else {
        myDisplay.printMessage("BT Only Mode");
    }
    
    Serial.println("System ready!");
}

void loop() {
    // Handle Bluetooth connection status
    bool currentBT = SerialBT.hasClient();
    if (currentBT != bluetoothConnected) {
        bluetoothConnected = currentBT;
        if (bluetoothConnected) {
            Serial.println("Bluetooth device connected!");
            SerialBT.println("Hello! ESP32 connected.");
        } else {
            Serial.println("Bluetooth device disconnected");
        }
    }
    
    // Handle incoming Bluetooth messages
    if (SerialBT.available()) {
        String message = SerialBT.readString();
        message.trim();
        
        Serial.print("BT received: ");
        Serial.println(message);
        
        // Simple responses
        if (message == "hello") {
            SerialBT.println("Hi there!");
        } else if (message == "status") {
            SerialBT.println("ESP32 is running fine!");
        } else {
            SerialBT.println("Got: " + message);
        }
    }
    
    // Potentiometer -> Display logic
    int val = myPot.read();
    int index = map(val, 0, 4095, 0, 1);
    index = constrain(index, 0, (sizeof(messages)/sizeof(messages[0])) - 1);
    
    if (index != msgIndex) {
        msgIndex = index;
        myDisplay.printMessage(messages[msgIndex]);
        Serial.print("Showing message: ");
        Serial.println(messages[msgIndex]);
        
        // Send via Bluetooth if connected
        if (bluetoothConnected) {
            SerialBT.println("Display: " + messages[msgIndex]);
        }
    }
    
    delay(100);
}