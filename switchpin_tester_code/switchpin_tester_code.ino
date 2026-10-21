#define switchpin A0
void setup() {
  pinMode(switchpin,INPUT_PULLUP);
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void loop() {
  int switchstate=analogRead(switchpin);
  Serial.println(switchstate);
  delay(500);
  // put your main code here, to run repeatedly:
  
}