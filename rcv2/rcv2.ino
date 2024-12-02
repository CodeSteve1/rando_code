 
#include <Wire.h>

#include "BluetoothSerial.h"

BluetoothSerial serialBT;

char btSignal;
int motor_max_spd=255;

// Motor A connections
const int ENA = 14;
const int IN1 = 26;
const int IN2 = 27;

// Motor B connections
const int ENB = 15;
const int IN3 = 2;
const int IN4 = 4;

int T_Spd=150;


int mode=0;

void setup() {
  // Initialize motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
  
  // Initialize the magnetometer




    if (!serialBT.begin("VIRUS_ESP32")) {
    //Serial.println("An error occurred initializing Bluetooth");
  } else {
   // Serial.println("Bluetooth initialized successfully");
  }
}

void loop() {
  //turn_angle(90);
  //delay(1000);  // Delay to avoid constant turning, adjust as needed
 // turn_angle(120);
 // delay(2000);
  //turn_angle(-90);
  if (mode==0){
    if (serialBT.available()) {
    // Read one character from the Bluetooth serial
    btSignal = serialBT.read();
    // Print the received character to the serial monitor
    Serial.print("Received: ");
    Serial.println(btSignal);

    if (btSignal=='F'){
      moveForward();
    }
    else if(btSignal=='S'){
      stopMotors();
    }
    else if(btSignal=='B'){
      moveBackward();
    }
    else if(btSignal=='R'){
      turnRight();
    }
    else if(btSignal=='L'){
      turnLeft();
    }
  }

  }
}

void moveForward() {
  Serial.println("Moving forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, motor_max_spd); // Full speed

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, motor_max_spd); // Full speed
}

void moveBackward() {
  Serial.println("Moving backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, motor_max_spd); // Full speed

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, motor_max_spd); // Full speed
}

void turnLeft() {
  Serial.println("Turning left");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, T_Spd); // Adjust speed as needed

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, T_Spd); // Adjust speed as needed
}

void turnRight() {
  Serial.println("Turning right");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, T_Spd); 

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, T_Spd); 
}

void stopMotors() {
  Serial.println("Stopping motors");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0); 
}



