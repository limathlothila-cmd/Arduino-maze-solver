// --- Pin Definitions ---
// Note: Update these pin numbers to match your actual Arduino wiring!

// Ultrasonic Sensors
#define trigLeft A0
#define echoLeft A1
#define trigFront A2
#define echoFront A3
#define trigRight A4
#define echoRight A5

// Motor Control (L298N)
#define motorEnA 9   // Must be a PWM pin (~)
#define motorIn1 8
#define motorIn2 7
#define motorEnB 10  // Must be a PWM pin (~)
#define motorIn3 5
#define motorIn4 4

// Sensors & Inputs
#define IRpin 2      // Floor color sensor
#define switchPin 3  // Left/Right hand rule toggle
#define buzzerPin 12 // University provided buzzer

// --- Tuning Variables ---
// Change these values here rather than hunting through the code
const int baseSpeed = 177;
const int turnSpeed = 177;
const int turnTime90 = 600;  // Milliseconds needed to turn 90 degrees (You must calibrate this)
const int turnTime180 = 1200; // Milliseconds needed to turn 180 degrees (You must calibrate this)

const float sideWallThreshold = 10.0;
const float frontWallThreshold = 5.0; // Increased slightly from 4.25 for safety

void setup() {
  pinMode(trigLeft, OUTPUT);
  pinMode(echoLeft, INPUT);
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
  pinMode(trigRight, OUTPUT);
  pinMode(echoRight, INPUT);
  
  pinMode(IRpin, INPUT);
  pinMode(switchPin, INPUT_PULLUP); // Using internal pullup for the switch
  pinMode(buzzerPin, OUTPUT);
  
  pinMode(motorEnA, OUTPUT);
  pinMode(motorEnB, OUTPUT);
  pinMode(motorIn1, OUTPUT);
  pinMode(motorIn2, OUTPUT);
  pinMode(motorIn3, OUTPUT);
  pinMode(motorIn4, OUTPUT);
  
  Serial.begin(9600);
}

// --- Motor Control Functions ---

void forward() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorEnA, baseSpeed);
  analogWrite(motorEnB, baseSpeed);
}

void stopMotors() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorEnA, 0);
  analogWrite(motorEnB, 0);
}

void turnLeft90() {
  digitalWrite(motorIn1, LOW);
  digitalWrite(motorIn2, HIGH);
  digitalWrite(motorIn3, HIGH);
  digitalWrite(motorIn4, LOW);
  analogWrite(motorEnA, turnSpeed);
  analogWrite(motorEnB, turnSpeed);
  delay(turnTime90); // Use the variable defined at the top
  stopMotors();      // Always stop after a turn
}

void turnRight90() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
  analogWrite(motorEnA, turnSpeed);
  analogWrite(motorEnB, turnSpeed);
  delay(turnTime90);
  stopMotors();
}

void turn180() {
  digitalWrite(motorIn1, HIGH);
  digitalWrite(motorIn2, LOW);
  digitalWrite(motorIn3, LOW);
  digitalWrite(motorIn4, HIGH);
  analogWrite(motorEnA, turnSpeed);
  analogWrite(motorEnB, turnSpeed);
  delay(turnTime180);
  stopMotors();
}

// --- Sensor Reading ---

float distanceCal(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  // Added a timeout of 25000us (~400cm) so the code doesn't freeze if no echo is received
  unsigned long duration = pulseIn(echo, HIGH, 25000); 
  
  if (duration == 0) return 999.0; // Return a large number if nothing is detected
  
  float distance = duration * 0.034 / 2;
  return distance;
}

// --- Maze Solving Logic ---

void leftHandMethod(float leftDist, float frontDist, float rightDist) {
  if (leftDist > sideWallThreshold) {
    stopMotors();
    delay(200); // Brief pause before turning for stability
    turnLeft90();
  } else if (frontDist > frontWallThreshold) {
    forward();
  } else if (rightDist > sideWallThreshold) {
    stopMotors();
    delay(200);
    turnRight90();
  } else {
    stopMotors();
    delay(200);
    turn180();
  }
}

void rightHandMethod(float leftDist, float frontDist, float rightDist) {
  if (rightDist > sideWallThreshold) {
    stopMotors();
    delay(200);
    turnRight90();
  } else if (frontDist > frontWallThreshold) {
    forward();
  } else if (leftDist > sideWallThreshold) { // Fixed typo "lefttdistance"
    stopMotors();
    delay(200);
    turnLeft90();
  } else {
    stopMotors();
    delay(200);
    turn180();
  }
}

// --- Main Loop ---

void loop() {
  float leftLength = distanceCal(trigLeft, echoLeft);
  float frontLength = distanceCal(trigFront, echoFront);
  float rightLength = distanceCal(trigRight, echoRight); // Fixed typo "rightlengthe"
  
  int IRvalue = digitalRead(IRpin);
  int switchState = digitalRead(switchPin);

  // Check for Finish Line
  // Most IR sensors return LOW when reflecting off a white surface
  if (IRvalue == LOW) { 
    stopMotors();
    digitalWrite(buzzerPin, HIGH); // Sound buzzer to indicate finish
    while(true) {
      // Endless loop to keep the robot stopped at the finish tile
      delay(1000); 
    }
  }

  // Navigate Maze
  if (switchState == HIGH) {
    rightHandMethod(leftLength, frontLength, rightLength);
  } else {
    leftHandMethod(leftLength, frontLength, rightLength);
  }
  
  // Small delay to prevent overwhelming the ultrasonic sensors
  delay(50); 
}
