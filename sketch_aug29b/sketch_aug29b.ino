#include <SPI.h>
#include <LoRa.h>

#include <Servo.h>

// Create Servo objects for two ESCs
Servo esc;
Servo esc2;

int servoPin = 22;  // Pin connected to the first ESC control wire
int servoPin2 = 13; // Pin connected to the second ESC control wire
// define the pins used by the transceiver module
#define ss 5
#define rst 14
#define dio0 2

void setup() {
  // initialize Serial Monitor
  Serial.begin(115200);
  while (!Serial);
  Serial.println("LoRa Receiver");

  // setup LoRa transceiver module
  LoRa.setPins(ss, rst, dio0);
  
    esc.attach(servoPin);
  esc2.attach(servoPin2);
  // replace the LoRa.begin() argument with your location's frequency 
  while (!LoRa.begin(433E6)) {
    Serial.println(".");
    delay(500);
  }
  
  // Change sync word (0xF3) to match the receiver
  LoRa.setSyncWord(0xF3);
  Serial.println("LoRa Initializing OK!");

  esc.writeMicroseconds(1000);   // Sends a signal to stop the motor (minimum throttle)
  esc2.writeMicroseconds(1000);  // Sends a signal to stop the motor (minimum throttle)
  delay(1000);  
}

void motor_speed(int throttle,int turn){
    int x=map(throttle,0,100,1000,1500);
    int mot1=x;
    int mot2=x;
    if(turn==1){
      mot1+=500;
    }
    else if(turn==2){
      mot2+=500;
    }
      esc.writeMicroseconds(mot1);   // Full throttle
      esc2.writeMicroseconds(mot2);  // Full throttle

    
}
void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");

    // read the entire packet as a string
    String receivedString = LoRa.readString();
    Serial.println(receivedString);
    
    // Find the positions of the commas
    int firstComma = receivedString.indexOf(',');
    int secondComma = receivedString.indexOf(',', firstComma + 1);

    // Extract the substrings and convert them to integers
    int mode = receivedString.substring(0, firstComma).toInt();
    int throttle = receivedString.substring(firstComma + 1, secondComma).toInt(); // +1 to skip the comma
    int turn = receivedString.substring(secondComma + 1).toInt();
    
    // Print the integers to verify
    Serial.print("a = ");
    Serial.println(mode);
    Serial.print("b = ");
    Serial.println(throttle);
    Serial.print("c = ");
    Serial.println(turn);


    if (mode==0){
      //set servo=0;
      motor_speed(throttle,turn);
    }
    else if(mode==1){
      //set servo 90;
      motor_speed(throttle,turn);
    }

  }
}
