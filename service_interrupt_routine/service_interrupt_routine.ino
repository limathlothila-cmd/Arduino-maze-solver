const int IRsensor=2;
//const byte whitesquaredetected=LOW;


void setup() {
  pinMode(IRsensor,INPUT);
  attachInterrupt(digitalPinToInterrupt(IRsensor), stopmotors, FALLING);
}

void loop() {
  digitalWrite(ledPin, state);
}

void whitedetected() {
  whitesquaredetected=!whitesquaredetected;

}

void stopmotors(){

}