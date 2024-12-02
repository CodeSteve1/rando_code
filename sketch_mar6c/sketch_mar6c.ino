/*
  Example of BH1750 library usage. This example initialises the BH1750 object using the default high resolution continuous mode and then makes a light level reading every second.
*/

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
const int ledPin = 16;  // 16 corresponds to GPIO16

// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int night_brightness=255;
int sunrise_brightness=50;
int noon_brightness=0;
int sunset_brightness=150;

void setup(){
  Serial.begin(9600);

  // Initialize the I2C bus (BH1750 library doesn't do this automatically)
  Wire.begin();
  // On esp8266 you can select SCL and SDA pins using Wire.begin(D4, D3);
  // For Wemos / Lolin D1 Mini Pro and the Ambient Light shield use Wire.begin(D2, D1);
    // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));

}

void loop() {
  float lux = lightMeter.readLightLevel();
    if( lux<50){
      ledcWrite(ledChannel,night_brightness);
      Serial.print("night");}
    else if(lux>50 && lux<300){
      ledcWrite(ledChannel,sunrise_brightness);
      Serial.print("sunrise or sunset");}
    else if( lux>300){
      ledcWrite(ledChannel,noon_brightness);
      Serial.print("Morning!");}
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
  delay(2000);
}