// Pin Definitions
#define RPWM_PIN_MOTOR1 5   // Right PWM pin
#define LPWM_PIN_MOTOR1 18   // Left PWM pin
#define R_EN_PIN_MOTOR1 19   // Right enable pin
#define L_EN_PIN_MOTOR1 21   // Left enable pin

// PWM Settings
#define PWM_FREQ 5000      // Frequency in Hz 5000 has an audible noise
#define PWM_RESOLUTION 8   // 8-bit resolution (0-255)
#define PWM_CHANNEL_R_MOT1 0    // PWM channel for RPWM
#define PWM_CHANNEL_L_MOT1 1    // PWM channel for LPWM

int speed = 0; // Speed variable (0-255)

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);

  // Enable motor driver
  pinMode(R_EN_PIN_MOTOR1, OUTPUT);
  pinMode(L_EN_PIN_MOTOR1, OUTPUT);
  digitalWrite(R_EN_PIN_MOTOR1, HIGH);
  digitalWrite(L_EN_PIN_MOTOR1, HIGH);

  // Configure PWM channels and attach them to pins
  ledcAttachChannel(RPWM_PIN_MOTOR1, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL_R_MOT1);
  ledcAttachChannel(LPWM_PIN_MOTOR1, PWM_FREQ, PWM_RESOLUTION, PWM_CHANNEL_L_MOT1);
}

void loop() {
  // Increase speed gradually
  /*for (speed = 0; speed <= 255; speed += 5) {
    setMotorSpeed(speed, true); // true for forward direction
    Serial.println("Forward Speed: " + String(speed)); // Print speed
    delay(100);
  }

  // Decrease speed gradually
  for (speed = 255; speed >= 0; speed -= 5) {
    setMotorSpeed(speed, true); // true for forward direction
    Serial.println("Forward Speed: " + String(speed)); // Print speed
    delay(100);
  }

  delay(1000); // Pause for 1 second

  // Reverse direction
  for (speed = 0; speed <= 255; speed += 5) {
    setMotorSpeed(speed, false); // false for reverse direction
    Serial.println("Reverse Speed: " + String(speed)); // Print speed
    delay(100);
  }

  for (speed = 255; speed >= 0; speed -= 5) {
    setMotorSpeed(speed, false); // false for reverse direction
    Serial.println("Reverse Speed: " + String(speed)); // Print speed
    delay(100);
  }

  delay(1000); // Pause for 1 second*/
  setMotorSpeed(255,true);
}

// Function to control motor speed and direction
void setMotorSpeed(int speed, bool forward) {
  if (forward) {
    ledcWriteChannel(PWM_CHANNEL_R_MOT1, speed); // Forward direction
    ledcWriteChannel(PWM_CHANNEL_L_MOT1, 0);    // No reverse
  } else {
    ledcWriteChannel(PWM_CHANNEL_R_MOT1, 0);    // No forward
    ledcWriteChannel(PWM_CHANNEL_L_MOT1, speed); // Reverse direction
  }
}
