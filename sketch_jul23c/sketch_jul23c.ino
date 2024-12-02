//Defining header Files

#include <ModbusMaster.h>

#define MAX485_DE_RE 18

ModbusMaster node; //object node for class ModbusMaster

void preTransmission()
{
  digitalWrite(MAX485_DE_RE, HIGH);
}

void postTransmission()
{
  digitalWrite(MAX485_DE_RE, LOW);
}

void setup()
{
  pinMode(MAX485_DE_RE, OUTPUT);

  digitalWrite(MAX485_DE_RE, LOW);

  Serial.begin(115200);
  // Transmission mode: MODBUS-RTU, Baud rate: 9600bps, Data bits: 8, Stop bit: 1, Check bit: no
  Serial1.begin(9600, SERIAL_8N1, 21, 23);

  // Slave address: the factory default is 01H (set according to the need, 00H to FCH)
  node.begin(1, Serial1);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}
//Setup ends here

void loop()
{
  // The 03H Function Code Example: Read The Atmospheric Temperature, Humidity & Pressure
  // Host Scan Order (Slave addr:0x01): 01 03 00 00 00 03 05CB
  // Slave Response: 01 03 06 01 21 0164 2728 C76E
  // Address of the first register Lo bytes is 00
  // Number of registers of Lo bytes is 03 
  uint8_t result = node.readHoldingRegisters( 0x7529, 3 );
  Serial.print("result = ");
  Serial.println( result );

  delay (1000);
  
  if (result == node.ku8MBSuccess)
  {
    Serial.print("v1");
    Serial.print(node.getResponseBuffer(0));
    Serial.println("");
    Serial.print("v2");
    Serial.print(node.getResponseBuffer(1));
    Serial.println("");
    Serial.print("v3");
    Serial.print(node.getResponseBuffer(2));
    Serial.println("");
  }
  
  Serial.print("\n");
  delay(1000);}

