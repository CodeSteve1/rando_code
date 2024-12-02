#include <ModbusMaster.h>

#define MAX485_DE_RE 18

ModbusMaster node; // Object node for class ModbusMaster

void preTransmission() {
  digitalWrite(MAX485_DE_RE, HIGH);
}

void postTransmission() {
  digitalWrite(MAX485_DE_RE, LOW);
}

void setup() {
  pinMode(MAX485_DE_RE, OUTPUT);
  digitalWrite(MAX485_DE_RE, LOW);

  Serial.begin(115200); // Debugging serial
  // Transmission mode: MODBUS-RTU, Baud rate: 9600bps, Data bits: 8, Stop bit: 1, Check bit: no
  Serial1.begin(9600, SERIAL_8N1, 21, 23); // Modbus serial

  // Initialize Modbus communication
  node.begin(1, Serial1); // Slave address 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  result = node.readHoldingRegisters(0x7530, 1); //752f
  if (result == node.ku8MBSuccess) {
    float voltageV1N = node.getResponseBuffer(0) ;
    Serial.print("Voltage V1N: ");
    Serial.print(voltageV1N);
    Serial.println(" V");
  } else {
    Serial.print("Failed to read Voltage V1N, result code: ");
    Serial.println(result);
  }
  delay(1000);
  result = node.readHoldingRegisters(30002, 1);
  if (result == node.ku8MBSuccess) {
    float voltageV2N = node.getResponseBuffer(0) ;
    Serial.print("Voltage V2N: ");
    Serial.print(voltageV2N);
    Serial.println(" V");
  } else {
    Serial.print("Failed to read Voltage V2N, result code: ");
    Serial.println(result);
  }
  delay(1000);

  result = node.readHoldingRegisters(30016, 1);
  if (result == node.ku8MBSuccess) {
    float currentI1 = node.getResponseBuffer(0) / 10.0;
    Serial.print("Current I1: ");
    Serial.print(currentI1);
    Serial.println(" A");
  } else {
    Serial.print("Failed to read Current I1, result code: ");
    Serial.println(result);
  }
  delay(1000);

  // Continue similarly for other parameters...
}
