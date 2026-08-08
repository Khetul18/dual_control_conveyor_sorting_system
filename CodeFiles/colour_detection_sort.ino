#include <Servo.h> // Include servo library

// Pin configuration
#define OE 9    // Output Enable (active LOW)
#define S0 11
#define S1 10
#define S2 6
#define S3 5
#define sensorOut 7 // Sensor OUT pin

Servo myServo;          // Create servo object
const int servoPin = A2; // Servo control pin

int red = 0;
int green = 0;
int blue = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(sensorOut, INPUT);

  digitalWrite(S0, HIGH); // 20% frequency scaling
  digitalWrite(S1, LOW);
  digitalWrite(OE, LOW);  // Enable sensor output

  myServo.attach(servoPin); // Attach servo to pin A2
  myServo.write(0);         // Set initial position to 0°

  Serial.begin(9600);       // Start serial communication
}

void loop() {
  red = getAverageColor(LOW, LOW, 10);       // RED filter
  green = getAverageColor(HIGH, HIGH, 10);   // GREEN filter
  blue = getAverageColor(LOW, HIGH, 10);     // BLUE filter

  Serial.print("R = ");
  Serial.print(red);
  Serial.print(" G = ");
  Serial.print(green);
  Serial.print(" B = ");
  Serial.println(blue);

  // If average green value is less than 80, move servo
  if (green < 80) {
    Serial.println("Green object detected!");
    delay(1000);          // Wait 1 second
    myServo.write(100);   // Move servo to 100°
    delay(9000);          // Hold for 9 seconds
    myServo.write(0);     // Return servo to 0°
  }

  delay(500); // Slight delay between readings
}

// Function to take multiple readings and return average
int getAverageColor(int s2State, int s3State, int samples) {
  digitalWrite(S2, s2State);
  digitalWrite(S3, s3State);

  long total = 0;
  for (int i = 0; i < samples; i++) {
    total += pulseIn(sensorOut, LOW, 100000); // Read pulse (with 100ms timeout)
    delay(10);
  }
  return total / samples; // Return average
}