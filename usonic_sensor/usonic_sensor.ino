#define trigL 4
#define echoL 2
/*#define trigF 3
#define echoF 4
#define trigR 5
#define echoR 6*/


void setup() {
  Serial.begin(9600);
  pinMode(trigL,OUTPUT);
  /*pinMode(trigF,OUTPUT);
  pinMode(trigR,OUTPUT);*/
  pinMode(echoL,INPUT);
 /* pinMode(echoF,INPUT);
  pinMode(echoR,INPUT);*/


}


float distancecal(int trig,int echo){
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

unsigned long duration=pulseIn(echo,HIGH,25000);
float distance=duration*0.034/2;
return distance;
}

void loop() {

float leftdistance= distancecal(trigL,echoL) ;
delay(100);
Serial.println(leftdistance);
/*float frontdistance= distancecal(trigF,echoF) ;
float rightdistance= distancecal(trigR,echoR) ;*/

  // put your main code here, to run repeatedly:

}
