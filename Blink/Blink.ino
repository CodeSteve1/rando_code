/*
  
*/
int pin=D0;
int c=0;
boolean newData = false;
float k=1000;
void setup() {
  pinMode(pin, OUTPUT);

}


void loop() {
  for(;c<=100000000;c++){
    digitalWrite(pin,HIGH);
    delay(k);                      
    digitalWrite(pin, LOW);  
    delay(k);
    k=k/1.02;

  }
 // while(1){
/*  digitalWrite(pin, HIGH);
  delay(1000);                      
  digitalWrite(pin, LOW);   
  delay(1000);
  // }   */                 
}
