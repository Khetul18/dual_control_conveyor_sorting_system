#include <Servo.h>

// === Metal Detection ===
const int sensorPin = A0;
unsigned long lastSensorTime = 0;
const unsigned long sensorDelay = 200;
bool metalDetected = false;

// === Stepper Motor ===
const int dirPin = 2;
const int stepPin = 3;
const unsigned long motorRunTime = 60000;
const unsigned long motorStepDelay = 5000;
unsigned long motorStartTime = 0;
unsigned long lastStepTime = 0;
bool motorOn = false;
bool stepState = false;

// === Servo Motor ===
Servo myServo;
const int servoPin = A1;
bool servoActive = false;
int servoStage = 0;
unsigned long servoStartTime = 0;

void setup() {
  Serial.begin(9600);

  // Metal detection pin
  pinMode(sensorPin, INPUT);

  // Stepper motor setup
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW); // Motor direction

  // Servo setup
  myServo.attach(servoPin);
  myServo.write(100); // Start at 100°
}

void loop() {
  // === Metal Detection ===
  if (millis() - lastSensorTime >= sensorDelay) {
    lastSensorTime = millis();
    int sensorValue = analogRead(sensorPin);
    Serial.print("Analog Value: ");
    Serial.println(sensorValue);

    if (sensorValue > 900 && !servoActive) {
      Serial.println("Metal detected");
      metalDetected = true;
      servoActive = true;
      servoStage = 0;
      servoStartTime = millis();
    } else {
      Serial.println("No metal");
    }
  }

  // === Stepper Motor Control ===
  if (!motorOn) {
    motorOn = true;
    motorStartTime = millis();
    lastStepTime = micros();
  }

  if (motorOn && millis() - motorStartTime < motorRunTime) {
    if (micros() - lastStepTime >= motorStepDelay) {
      lastStepTime = micros();
      digitalWrite(stepPin, stepState);
      stepState = !stepState;
    }
  }

  if (motorOn && millis() - motorStartTime >= motorRunTime) {
    motorOn = false;
    delay(1000); // Pause before restarting motor
  }

  // === Servo Motor Triggered by Metal Detection ===
  if (servoActive) {
    unsigned long currentTime = millis();

    if (servoStage == 0 && currentTime - servoStartTime >= 1000) {
      // After 1 sec: move to 0°
      myServo.write(0);
      servoStage = 1;
      servoStartTime = currentTime;
    }
    else if (servoStage == 1 && currentTime - servoStartTime >= 9000) {
      // After 9 sec at 0°, return to 100°
      myServo.write(100);
      servoStage = 2;
      servoActive = false; // Sequence complete
    }
  }
}