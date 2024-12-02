
const int ledPin = D0; 

void setup() {
  
}

void loop() {
  
  for(int dutyCycle = 0; dutyCycle < 255; dutyCycle++){   
    
    analogWrite(ledPin, dutyCycle);
    delay(1);
  }

  
  for(int dutyCycle = 255; dutyCycle > 0; dutyCycle--){
   
    analogWrite(ledPin, dutyCycle);
    delay(1);
  }
}