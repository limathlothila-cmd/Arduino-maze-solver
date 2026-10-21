
const int IRsensor=2;

void setup() {
   pinMode(IRsensor,INPUT);
   Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
 bool state=digitalRead(IRsensor);
  Serial.println(state);
  delay(500);
  // put your main code here, to run repeatedly:

}
