/*********
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp32-dc-motor-l298n-motor-driver-control-speed-direction/
*********/

// Motor A
int motor1Pin1 = 33; 
int motor1Pin2 = 25; 
int enable1Pin = 32; 
int motor2Pin1 = 27; 
int motor2Pin2 = 26; 
const int freq = 30000;
const int pwmChannel = 0;
const int pwmChannel2 = 2;
const int resolution = 8;
int dut=0;
int dut2=0;


void setup() {
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(14,OUTPUT);

  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);


    // configure LED PWM functionalitites
  ledcSetup(pwmChannel2, 10000, 8);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(14, pwmChannel2);
  

  Serial.begin(115200);

  // testing
  Serial.print("Testing DC Motor...");
}

void loop() {
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(14,HIGH);
  // Move the DC motor forward at maximum speed
  Serial.println("Moving Forward");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, HIGH);  
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  // Move DC motor backwards at maximum speed
  Serial.println("Moving Backwards");
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW); 
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);
  delay(2000);

  // Stop the DC motor
  Serial.println("Motor stopped");
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, LOW);
  digitalWrite(motor2Pin2, LOW);
  delay(1000);

  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  digitalWrite(motor2Pin1, HIGH);
  digitalWrite(motor2Pin2, LOW);

  while (dut <= 255){
  ledcWrite(pwmChannel, dut);
  ledcWrite(pwmChannel2, dut);
  Serial.print("Forward with duty cycle: ");
  Serial.println(dut);
  Serial.print("turn with duty cycle: ");
  Serial.println(dut2);
  dut = dut + 5;
  delay(500);


}
dut=0;


  while (dut <= 255){
  ledcWrite(pwmChannel, dut);
  ledcWrite(pwmChannel2, dut);
  Serial.print("Forward with duty cycle: ");
  Serial.println(dut);
  Serial.print("turn with duty cycle: ");
  Serial.println(dut2);
  dut = dut + 5;
  delay(500);
}
dut=0;

  // Move DC motor forward with increasing speed

}