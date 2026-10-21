#define trigerleft 2
#define echoleft 3
#define trigerfront 4
#define echofront 5
#define trigerright A1
#define echoright A2
#define IRpin A0
#define switchpin A3

#define motorenA 6
#define motorenB 11
#define motorin1 7
#define motorin2 8
#define motorin3 12
#define motorin4 13

// Thresholds for detecting walls at the center of a tile
const float sidewallthreshold = 13.0;
const float frontwallthreshold = 12.0; 

// Timings calibrated for 1 tile length (22.5 cm) and turning
const int TILE_DRIVE_TIME = 600; // Duration to advance 1 full cell
const int PAUSE_TIME      = 150; // Pause at cell center to let sensors stabilize

void setup() {
  pinMode(trigerleft, OUTPUT);
  pinMode(echoleft, INPUT);
  pinMode(trigerfront, OUTPUT);
  pinMode(echofront, INPUT);
  pinMode(trigerright, OUTPUT);
  pinMode(echoright, INPUT);
  
  //pinMode(IRpin, INPUT);
 // pinMode(switchpin, INPUT_PULLUP);
  
  pinMode(motorenA, OUTPUT);
  pinMode(motorenB, OUTPUT);
  pinMode(motorin1, OUTPUT);
  pinMode(motorin2, OUTPUT);
  pinMode(motorin3, OUTPUT);
  pinMode(motorin4, OUTPUT);
  
  Serial.begin(9600);
  delay(1000);
}

// Check finish tile condition continuously during forward movement
/*bool checkFinish() {
  if (digitalRead(IRpin) == HIGH) { // Adjust HIGH/LOW based on active floor state
    stopMotors();
    return true;
  }
  return false;
}*/

// Drives forward exactly 1 tile while monitoring IR sensor
void forwardOneTile() {
  digitalWrite(motorin1, LOW);
  digitalWrite(motorin2, HIGH);
  digitalWrite(motorin3, LOW);
  digitalWrite(motorin4, HIGH);
  analogWrite(motorenA, 80);
  analogWrite(motorenB, 55);

  /*unsigned long startTime = millis();
  while (millis() - startTime < TILE_DRIVE_TIME) {
    if (checkFinish()) return;
    delay(10);
  }*/
  stopMotors();
}

void stopMotors() {
  digitalWrite(motorin1, LOW);
  digitalWrite(motorin2, LOW);
  digitalWrite(motorin3, LOW);
  digitalWrite(motorin4, LOW);
  analogWrite(motorenA, 0);
  analogWrite(motorenB, 0);
}

void turnleft90() {
  digitalWrite(motorin1, LOW);
  digitalWrite(motorin2, HIGH);
  digitalWrite(motorin3, HIGH);
  digitalWrite(motorin4, LOW);
  analogWrite(motorenA, 80);
  analogWrite(motorenB, 80);
  delay(320);
  stopMotors();
}

void turnright90() {
  digitalWrite(motorin1, HIGH);
  digitalWrite(motorin2, LOW);
  digitalWrite(motorin3, LOW);
  digitalWrite(motorin4, HIGH);
  analogWrite(motorenA, 80);
  analogWrite(motorenB, 80);
  delay(320);
  stopMotors();
}

void turn180() {
  digitalWrite(motorin1, HIGH);
  digitalWrite(motorin2, LOW);
  digitalWrite(motorin3, LOW);
  digitalWrite(motorin4, HIGH);
  analogWrite(motorenA, 80);
  analogWrite(motorenB, 80);
  delay(640);
  stopMotors();
}

float distancecal(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  unsigned long duration = pulseIn(echo, HIGH, 25000);
  if (duration == 0) return 999.0;
  return (duration * 0.034 / 2);
}

// Left-Hand Rule (Tile-by-Tile)
void lefthandmethod(float leftdistance, float frontdistance, float rightdistance) {
  if (leftdistance > sidewallthreshold) {
    turnleft90();
    forwardOneTile();
  } else if (frontdistance > frontwallthreshold) {
    forwardOneTile();
  } else if (rightdistance > sidewallthreshold) {
    turnright90();
    forwardOneTile();
  } else {
    turn180();
    forwardOneTile();
  }
}

// Right-Hand Rule (Tile-by-Tile)
void righthandmethod(float leftdistance, float frontdistance, float rightdistance) {
  if (rightdistance > sidewallthreshold) {
    turnright90();
    forwardOneTile();
  } else if (frontdistance > frontwallthreshold) {
    forwardOneTile();
  } else if (leftdistance > sidewallthreshold) {
    turnleft90();
    forwardOneTile();
  } else {
    turn180();
    forwardOneTile();
  }
}

void loop() {
  // 1. Check if robot is on the finish tile
  /*if (digitalRead(IRpin) == HIGH) { // Adjust HIGH/LOW if needed for white floor
    stopMotors();
    while (true) {
      delay(1000);
    }
  }*/

  // 2. Measure distances from current tile center
  float leftlength  = distancecal(trigerleft, echoleft);
  float frontlength = distancecal(trigerfront, echofront);
  float rightlength = distancecal(trigerright, echoright);

  // 3. Switch between Left-Hand and Right-Hand methods
 /* int switchstate = digitalRead(switchpin);
  if (switchstate == HIGH) {
    righthandmethod(leftlength, frontlength, rightlength);
  } else {
    lefthandmethod(leftlength, frontlength, rightlength);
  }*/
righthandmethod(leftlength, frontlength, rightlength);
  // Brief pause at tile center before taking next readings
  stopMotors();
  delay(PAUSE_TIME);
}