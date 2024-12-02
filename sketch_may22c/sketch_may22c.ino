const int ENB = 15;
const int IN3 = 4;
const int IN4 = 2;

const int ENA = 27;
const int IN1 = 12;
const int IN2 = 14;

int T_Spd=150;
int tolerance=15;

int motor_max_spd=255;


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

void setup() {
  // put your setup code here, to run once:
    pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);

}

void loop() {
  // put your main code here, to run repeatedly:
  moveForward();

}
