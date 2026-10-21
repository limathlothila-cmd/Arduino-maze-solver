const int IRsensor=2;
#define motorenA 6
#define motorenB 11
#define motorin1 7
#define motorin2 8 
#define motorin3 12
#define motorin4 13

volatile bool white=false;

void setup() {
  pinMode(IRsensor,INPUT);
  pinMode(motorin1,OUTPUT);
  pinMode(motorin2,OUTPUT);
  pinMode(motorin3,OUTPUT);
  pinMode(motorin4,OUTPUT);
  pinMode(motorenA,OUTPUT);
  pinMode(motorenB,OUTPUT);
  attachInterrupt(digitalPinToInterrupt(IRsensor), whitedetected, RISING);
  // put your setup code here, to run once:

}

void loop() {
  if(!white){
    digitalWrite(motorin1,LOW);
    digitalWrite(motorin2,HIGH);
    digitalWrite(motorin3,LOW);
    digitalWrite(motorin4,HIGH);
    analogWrite(motorenA,65);//right wheel
    analogWrite(motorenB,49);
    delay(1000);
  }else{
    digitalWrite(motorin1,LOW);
    digitalWrite(motorin2,LOW);
    digitalWrite(motorin3,LOW);
    digitalWrite(motorin4,LOW);
    analogWrite(motorenA,0);//right wheel
    analogWrite(motorenB,0);
  }
  // put your main code here, to run repeatedly:

}

void whitedetected(){
  white=!white;
}
