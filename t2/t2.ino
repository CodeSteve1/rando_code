#include "BluetoothSerial.h"
BluetoothSerial serialBT;
char btSignal;
int motor_max_spd=255;


const int ENA = 14;
const int IN1 = 26;
const int IN2 = 27;

// Motor B connections
const int ENB = 15;
const int IN3 = 4;
const int IN4 = 2;

int T_Spd=150;
int tolerance=15;

void setup() {
  // put your setup code here, to run once:
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
  if (!serialBT.begin("ESP32")) {
    Serial.println("An error occurred initializing Bluetooth");
  } else {
    Serial.println("Bluetooth initialized successfully");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
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
  analogWrite(ENA, T_Spd); // Adjust speed as needed

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, T_Spd); // Adjust speed as needed
}

void stopMotors() {
  Serial.println("Stopping motors");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0); // Stop

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0); // Stop
}