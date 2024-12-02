int pin=A0;

int o=9.27;
int led=D0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(1200);
  Serial.println("enter input:");

}


void loop() {
  // put your main code here, to run repeatedly:
  int x=analogRead(pin);
  Serial.println(x);
  int per=x/o;
  int du=((per*2.55)/10)*10;
  digitalWrite(led,du);
  delay(100);

}
