/*
  Example of BH1750 library usage. This example initialises the BH1750 object using the default high resolution continuous mode and then makes a light level reading every second.
*/

#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;
const int ledPin = 16;  // 16 corresponds to GPIO16 to leds...
//connect out 1 and out 2 to  motor from l298n module
// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
int night_brightness=255;
int sunrise_brightness=50;
int noon_brightness=0;
int sunset_brightness=150;
const int trig=5; // connect trig from ultra to gpio 5
const int echo=18;// connect echo from ultra to gpio 18
int motorpin= 2;//connect gpio 2 to motor in1 and gpio22 to motor in2
int en=23;//motor enabler from l298n module to 23 gpio
const int threshhold=10;
int sunrise_finder_var=10;

int ultra(){//returns the distance between water and the tank celing 
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

     // measure duration of pulse from ECHO pin
   float duration_us = pulseIn(echo, HIGH);

    // calculate the distance

    float distance_cm = 0.017 * duration_us;
    return(distance_cm);
}

void setup(){
  Serial.begin(9600);
  digitalWrite(en, HIGH);//ensbling the motor pin

  Wire.begin();//enabling the i2c for the bh1750 sensor

  ledcSetup(ledChannel, freq, resolution);//sensor parameters

  ledcAttachPin(ledPin, ledChannel);

  lightMeter.begin();

  Serial.println(F("BH1750 Test begin"));
  //enabling the motor pins
  pinMode(motorpin, OUTPUT);
  pinMode(en,OUTPUT);
  //enabling the ultrasonic sensor pins
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);

}

void loop() {
  float lux = lightMeter.readLightLevel();
  digitalWrite(motorpin,HIGH);//setting motor to off 
  //----------------------------------------------------------------------------------------------------
  //DAY
  //-------------------------------------------------------------------
    if( lux<50){ 
      ledcWrite(ledChannel,night_brightness);//the brightness of the leds are set to max
      Serial.println("night");
      sunrise_finder_var=0; //when vaiable is set to 0 it means the sunrise did not occur yet( this is to differentiate between the sunrise and sunset.....once the sunrise happens and it goes to noon the var becomes 1 differentiating between sunrise and sunset)
      digitalWrite(motorpin,HIGH);} //motor off 
  //=======================================================================================================
  //sunrise motor with motor off
  //=======================================================================================================
    else if(lux>50 && lux<300 && sunrise_finder_var==0 && ultra()<15){
      ledcWrite(ledChannel,sunrise_brightness);//the brightness is set to dutycycle 100
      Serial.println("sunrise tank full");
      digitalWrite(motorpin,HIGH);}//motor is set to off
  //=======================================================================================================
  //sunrise with motor on
  //=======================================================================================================
    else if(lux>50 && lux<300 && sunrise_finder_var==0 && ultra()>15){
      ledcWrite(ledChannel,sunrise_brightness);
      Serial.println("sunrise tank empty");
      digitalWrite(motorpin,LOW);}//motor is set to on
  //=======================================================================================================
  //                     Sunset
  //=======================================================================================================
    else if(lux>50 && lux<300 && sunrise_finder_var!=0){
      ledcWrite(ledChannel,sunrise_brightness);//leds duty cycle set to 100
      Serial.println("sunset");}
  //=======================================================================================================
  //                      Morning
  //=======================================================================================================
    else if( lux>300){
      ledcWrite(ledChannel,noon_brightness);//leds turned off
      Serial.println("Morning!");
      digitalWrite(motorpin,HIGH);//motor turned off
      sunrise_finder_var=1;}
  //===================================
  //ERROR
  //===================================
    else{
      Serial.print("ERROR");
    }
  //========================================================================================================
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
    
  Serial.print("cm");
  delay(20);
}