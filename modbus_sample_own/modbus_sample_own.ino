#include <ModbusMaster.h>

// instantiate ModbusMaster object
ModbusMaster node;

// RS485 control pins
const int DE_RE_PIN = 2;

// Pin definitions for Serial2
const int RXD2 = 16;
const int TXD2 = 17;

void preTransmission() {
  digitalWrite(DE_RE_PIN, HIGH);
}

void postTransmission() {
  digitalWrite(DE_RE_PIN, LOW);
}

void setup() {
  // Initialize Serial1 for communication with the computer
  Serial1.begin(9600);  // Adjust baud rate as needed for your computer communication
  Serial1.println("Serial1 started at 9600");

  // Initialize Serial2 for Modbus communication
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);  // Set baud rate to 19800 for Modbus
  Serial1.println("Serial2 started at 9600 for Modbus");

  // Define RS485 control pin
  pinMode(DE_RE_PIN, OUTPUT);
  digitalWrite(DE_RE_PIN, LOW);

  // Modbus communication setup
  node.begin(1, Serial2); // 1 is the Modbus slave ID, using Serial2 for Modbus
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  uint16_t data; // Variable to hold read data

  // Read register 43915 (Modbus address 43915 is often represented as 3915)
  uint16_t registerAddress = 30000; // Convert to zero-based address
  result = node.readHoldingRegisters(registerAddress, 20);

  if (result == node.ku8MBSuccess) {
    data = node.getResponseBuffer(0);
    Serial1.print("Register 30000: ");
    Serial1.println(data); // Print to Serial1 (computer)
    data = node.getResponseBuffer(1);
    Serial1.print("Register 30002: ");
    Serial1.println(data); // Print to Serial1 (computer)
    data = node.getResponseBuffer(2);
    Serial1.print("Register 30004: ");
    Serial1.println(data); // Print to Serial1 (computer)
    data = node.getResponseBuffer(8);
    Serial1.print("Register 30016: ");
    Serial1.println(data); // Print to Serial1 (computer)
    data = node.getResponseBuffer(9);
    Serial1.print("Register 30018: ");
    Serial1.println(data); // Print to Serial1 (computer)
    data = node.getResponseBuffer(10);
    Serial1.print("Register 30020: ");
    Serial1.println(data); // Print to Serial1 (computer)

  } else {
    Serial1.print("Failed to read register 43915, result: ");
    Serial1.println(result); // Print to Serial1 (computer)
  }

  delay(1000); // Delay between reads
}
