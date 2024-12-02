/*
  Rui Santos
  Complete project details at https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files.
  
  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.
*/

#include <esp_now.h>
#include <WiFi.h>
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 
int motor2Pin1 = 5; 
int motor2Pin2 = 4; 
int enable2Pin = 32;


/*int motor1Pin1 = 33; 
int motor1Pin2 = 25; 
int enable1Pin = 32; 
int motor2Pin1 = 27; 
int motor2Pin2 = 26; 
int enable2Pin = 14;*/

int dut=0;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;

// Setting PWM properties
const int freq2 = 10000;
const int pwmChannel2 = 4;


int dutyCycle = 200;


// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
    int acc;
    int turn;
    int mode;
} struct_message;

// Create a struct_message called myData
struct_message myData;


void setup() {
  //
  //digitalWrite(32,HIGH);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin,OUTPUT);
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);
    // configure LED PWM functionalitites
  ledcSetup(pwmChannel2, 10000, 8);
  ledcAttachPin(enable2Pin, pwmChannel2);


  // Initialize Serial Monitor
  Serial.begin(115200);
  
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  digitalWrite(enable1Pin, HIGH);
  digitalWrite(enable2Pin, HIGH);


  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("acc: ");
  Serial.println(myData.acc);
  Serial.print("turn: ");
  Serial.println(myData.turn);
  Serial.print("mode: ");
  Serial.println(myData.mode);

 // ledcWrite(pwmChannel, myData.acc);
  if ((myData.acc >160 )&&(myData.acc<170)){
    ledcWrite(pwmChannel,0);
  }
  else if ((myData.acc>=170)){
    dut=(int)(myData.acc-170)*3;
    Serial.print("dutfow1:");
    Serial.println(dut);
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    ledcWrite(pwmChannel,dut);
  }
  else{
    dut=(int)(160-myData.acc)*1.593;
    Serial.print("dutrev:");
    Serial.println(dut);
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    ledcWrite(pwmChannel,dut);

  }






  if ((myData.turn < 3200) && (myData.turn > 2200)) {
    Serial.println("Turn: Off");
    ledcWrite(pwmChannel2,0);
  } else if (myData.turn >= 3200) {
    Serial.println("Turn: Right");
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    ledcWrite(pwmChannel2,(int)((myData.turn-3200)/3.509));
    Serial.println((int)((myData.turn-3200)/3.509));
  } else if (myData.turn <= 2200) {
    Serial.println("Turn: Left");
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    ledcWrite(pwmChannel2,255);
    Serial.println((int)myData.turn/10);
  }
   // ledcWrite(pwmChannel2,0);
   delay(50);                             //
   ledcWrite(pwmChannel,0);               // Remove these lines after installing the antennas
   delay(1);                              //

}
 

 
void loop() {


}