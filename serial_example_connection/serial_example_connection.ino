
int mode,movement,angle,duration;
char *ptr;
void setup() {
  Serial.begin(115200);  // Initialize USB serial port
  
  
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Received from Raspberry Pi: ");
    Serial.println(data);


  // Convert String to char array
  char inputBuffer[data.length() + 1]; // +1 for null terminator
  data.toCharArray(inputBuffer, sizeof(inputBuffer));

  // Tokenize the string and parse integers
  ptr = strtok(inputBuffer, " ");
  mode = atoi(ptr);
  ptr = strtok(NULL, " ");
  movement = atoi(ptr);
  ptr = strtok(NULL, " ");
  angle = atoi(ptr);
  ptr = strtok(NULL, " ");
  duration = atoi(ptr);

  // Print the values of the variables
  Serial.print("mode=");
  Serial.println(mode);
  Serial.print("movement=");
  Serial.println(movement);
  Serial.print("angle=");
  Serial.println(angle);
  Serial.print("duration=");
  Serial.println(duration);



  }
}