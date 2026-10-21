// Define the Arduino pins connected to the L298N
const int enA = 6;   // PWM pin for speed control (Must be a PWM pin, usually marked with ~)
const int in1 = 7;   // Direction pin 1
const int in2 = 8; 
const int in3=12;
const int in4=13;
const int  enB=11; 
//#define trigerfront 4
//#define echofront 5
const float frontwallthreshold=8.0;// Direction pin 2



void setup() {
  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
   pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
     pinMode(enB, OUTPUT);
     //pinMode(trigerfront,OUTPUT);
    //pinMode(echofront,INPUT);
  
  // Set initial rotation direction (Forward)
  
  
}

float distancecal(int trig,int echo){
  digitalWrite(trig,LOW);
  delayMicroseconds(2);
  digitalWrite(trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);

  unsigned long duration=pulseIn(echo,HIGH,25000);
  if (duration==0) return 999.0;
  float distance=duration*0.034/2;
  return distance;
  }

void forward(){
    
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(enA,56);//left wheel
    analogWrite(enB,50);//right wheel

}

void backward(){
    
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(enA,65);
    analogWrite(enB,49);

}

void stop(){
  
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(enA,0);
    analogWrite(enB,0);
}

void turnleft90(){
  
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(enA,80);
    analogWrite(enB,80);
    delay(380);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(enA,0);
    analogWrite(enB,0);

}

void turnright90(){
  
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH);
    analogWrite(enA,90);
    analogWrite(enB,80);
    delay(350);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(enA,0);
    analogWrite(enB,0);


}


void turn180(){
  
    

   digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    digitalWrite(in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite(enA,80);
    analogWrite(enB,100);
    delay(630);
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,LOW);
    analogWrite(enA,0);
    analogWrite(enB,0);

}



void loop() {

 /* float frontlength= distancecal(trigerfront,echofront) ;*/
  forward();
  
 
 

 /*if (frontlength<frontwallthreshold){
   stop();
   }

delay(50);
backward();
delay(2000);

 
  /*stop();
  delay(1000);*/

  turnleft90();
  delay(2000);

/*stop();
  delay(1000);*/

  //turnright90();
  //delay(1000);
  
  //turn180();
  //delay(2000);

  //stop();*/


  
}