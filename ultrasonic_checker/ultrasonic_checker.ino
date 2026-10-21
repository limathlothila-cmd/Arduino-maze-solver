#define trigerfront 4
#define echofront 5
#define trigerleft 2
#define echoleft 9
#define trigerright A1
#define echoright A2

void setup(){
  pinMode(trigerfront, OUTPUT);
  pinMode(echofront, INPUT);
  pinMode(trigerleft, OUTPUT);
   pinMode(echoleft, INPUT);
  pinMode(trigerright, OUTPUT);
   pinMode(echoright, INPUT);
  Serial.begin(9600);
}

float distancecal(int trig,int echo){
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

unsigned long duration=pulseIn(echo,HIGH);
if (duration==0) return 999.0;
float distance=duration*0.034/2;
return distance;
}


void loop(){
   float frontlength= distancecal(trigerleft,echoleft) ;
   Serial.println(frontlength);
   delay(500);

}