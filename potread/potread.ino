void setup() {
    Serial.begin(115200);
}

void loop() {
    int pot_value = analogRead(35);  // Replace A0 with your actual pin
    Serial.println(pot_value);
    delay(500);
}