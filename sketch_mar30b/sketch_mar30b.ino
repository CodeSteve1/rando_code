ch=0;
boolean newData = false;
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    Serial.println("enter input:");

}
void recvOneChar() {
    if (Serial.available() > 0) {
        receivedChar = Serial.read();
        newData = true;
    }
}

void loop() {
  // put your main code here, to run repeatedly:

}
