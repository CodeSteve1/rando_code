/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
*********/
#include <Wire.h>


// Motor A connections
const int ENA = 14;
const int IN1 = 26;
const int IN2 = 27;

// Motor B connections
const int ENB = 0;
const int IN3 = 2;
const int IN4 = 4;

void setup() {
  // Initialize motor pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
  

}

void loop() {
moveForward();
}

void moveForward() {
  Serial.println("Moving forward");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 255); // Full speed

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 255); // Full speed
}

void moveBackward() {
  Serial.println("Moving backward");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 255); // Full speed

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 255); // Full speed
}

void turnLeft() {
  Serial.println("Turning left");
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 175); // Adjust speed as needed

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 175); // Adjust speed as needed
}

void turnRight() {
  Serial.println("Turning right");
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 100); // Adjust speed as needed

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, 100); // Adjust speed as needed
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

void turn_angle(int angle) {
  int data = mag_data();
  Serial.println(data);
  
  // Continuously turn right until the data is within the desired range
  while (data <= 110 || data >= 130) {
    turnRight();
    delay(100);  // Small delay to allow the turn to take effect
    data = mag_data(); // Update the data after turning
    Serial.println(data);
  }
  stopMotors();  // Stop motors once the desired angle is reached
}

int mag_data() {
  
}
