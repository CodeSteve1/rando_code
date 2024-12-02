#include "BluetoothSerial.h"
#include <Arduino.h>

// Create a BluetoothSerial object
BluetoothSerial serialBT;

// Variable to store the incoming Bluetooth signal
char btSignal;

void setup() {
  // Start the hardware serial for debugging at 115200 baud rate
  Serial.begin(115200);

  // Initialize Bluetooth with a device name
  if (!serialBT.begin("Steve's_ESP32")) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized successfully");
  }
}

void loop() {
  // Check if there are any bytes available to read from the Bluetooth serial
  if (serialBT.available()) {
    // Read one character from the Bluetooth serial
    btSignal = serialBT.read();
    // Print the received character to the serial monitor
    Serial.print("Received: ");
    Serial.println(btSignal);
  }

  // Add a small delay to prevent overwhelming the serial output
  delay(10);
}
