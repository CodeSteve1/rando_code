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
typedef struct struct_message {
  int acc;
  int turn;
  int mode;

} struct_message;

// Create a struct_message called myData
struct_message myData;

esp_now_peer_info_t peerInfo;


static const uint8_t image_data_Turbo[512] = {
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙█████∙█∙∙█∙███∙∙███∙∙∙███∙∙∙██∙∙∙██∙∙███∙∙███∙∙█████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙█∙∙∙█∙∙█∙█∙∙█∙█∙∙█∙█∙∙∙█∙∙█∙█∙█∙█∙█∙∙∙█∙█∙∙█∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙█∙∙∙█∙∙█∙███∙∙███∙∙█∙∙∙█∙∙█∙∙█∙∙█∙█∙∙∙█∙█∙∙█∙████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙█∙∙∙█∙∙█∙██∙∙∙█∙∙█∙█∙∙∙█∙∙█∙∙∙∙∙█∙█∙∙∙█∙█∙∙█∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙█∙∙∙█∙∙█∙█∙█∙∙█∙∙█∙█∙∙∙█∙∙█∙∙∙∙∙█∙█∙∙∙█∙█∙█∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙█∙∙∙████∙█∙∙█∙███∙∙∙███∙∙∙█∙∙∙∙∙█∙∙███∙∙██∙∙∙█████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙██████████∙██∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██████████∙██∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙██████████∙██∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██████████∙██∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙██∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙∙██∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙████████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙████████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙███∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙██∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙███∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙███∙██∙∙∙∙█∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙██∙∙∙∙∙██∙∙∙∙██∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙█████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙██∙∙∙∙∙∙∙∙███∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙∙███
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    // ████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████████
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf7, 0xd2, 0xe7, 0x1c, 0x63, 0x39, 0xcf, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0x12, 0x94, 0xa2, 0x55, 0x45, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0x12, 0xe7, 0x22, 0x49, 0x45, 0x2f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0x12, 0xc4, 0xa2, 0x41, 0x45, 0x28, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0x12, 0xa4, 0xa2, 0x41, 0x45, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0x1e, 0x97, 0x1c, 0x41, 0x39, 0x8f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0xff, 0xb0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfd, 0x83, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf1, 0xff, 0xb0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xfd, 0x83, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x30, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x83, 0x20, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x83, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x3f, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0x83, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xc7, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x30, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc1, 0xc6, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xec, 0x20, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x18, 0x30, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
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
    myData.acc=(int)dut_acc;
    myData.turn =y;
    myData.mode=1;
    Serial.println((int)dut_acc);
    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
    // Draw bitmap on the screen
  if ((myData.acc >160 )&&(myData.acc<170)){
  display.drawBitmap(0, 0, image_data_Turbo, 128, 64, 1);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(30, 23);
  // Display static text
  display.println(0);
  display.setCursor(90, 23);
  display.println("1");
  display.display();
  delay(50);
  display.clearDisplay(); 
  delay(1);
  }
  else if ((myData.acc>=170)){
    dut=(int)(myData.acc-170)*3/2.55;  //remove 2.55 to get dutycycle
      display.drawBitmap(0, 0, image_data_Turbo, 128, 64, 1);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30, 23);
  // Display static text
    display.println(dut);
    display.setCursor(90, 23);
  display.println("1");
  display.display();
  delay(50);
  display.clearDisplay(); 
  delay(1);

  }

  else{
    dut=(int)(myData.acc-160)*0.6274;
    display.drawBitmap(0, 0, image_data_Turbo, 128, 64, 1);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(30, 23);
  // Display static text
    display.println(dut);
    display.setCursor(90, 23);
    display.println("1");
  display.display();
  delay(50);
  display.clearDisplay(); 
  delay(1);


  }

  }

  // Send message via ESP-NOW

   


}