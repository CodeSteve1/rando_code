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
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeMonoBold9pt7b.h>
int pot1=35;
int pot2=32;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
int dut;
int modes=1;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0xD4,0x8A,0xFC,0x9F,0xFA,0x08};

// Structure example to send data
// Must match the receiver structure
typedef struct car_message {
  int mode;

} car_message;

typedef struct rem_messagea {
    int acc;

} rem_messagea;

// Create a struct_message called myData
car_message car;
rem_messagea rem;

esp_now_peer_info_t peerInfo;



void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
 // digitalWrite(enable1Pin, HIGH);
  //digitalWrite(enable2Pin, HIGH);


  memcpy(&car, incomingData, sizeof(car));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("mode: ");
  Serial.println(car.mode);

 // ledcWrite(pwmChannel, myData.acc);


}
void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();
  delay(2000); // Pause for 2 seconds
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);

  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
    // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}
void loop() {
  // Set values to send
  int x=analogRead(pot1);
  int y=analogRead(pot2);
  float dut_acc=x/16.058;
  float dut_turn=y/16.058;
  if(modes==1){
    rem.acc=1002;
    Serial.println((int)dut_acc);
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &rem, sizeof(rem));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

  }
  delay(100);

  // Send message via ESP-NOW

   


}
