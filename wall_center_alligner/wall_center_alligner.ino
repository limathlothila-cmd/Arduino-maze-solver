 #define trigerleft 2
  #define echoleft 9
  #define trigerfront 4
  #define echofront 5
  #define trigerright A1
  #define echoright A2
  //#define IRpin 3
  #define motorenA 6
  #define motorenB 11
  #define motorin1 7
  #define motorin2 8
  #define motorin3 12
  #define motorin4 13
  //#define switchpin
  
  //const float leftgap=13.0;
  const float errormargin=0;
  const float sidewallthreshold=22.5;
  const float frontwallthreshold=8.0;
  

  int basespeedenA=70;
  int basespeedenB=60;

double kp,ki,kd;
double dt,lasttime;
double integralError,prevError,currentError;// 0 get assigned to these global variables by default
double PIDcontroler(double error);
int robotstate=0;


void setup() {
   pinMode(trigerleft,OUTPUT);
    pinMode(echoleft,INPUT);
    pinMode(trigerfront,OUTPUT);
    pinMode(echofront,INPUT);
    pinMode(trigerright,OUTPUT);
    pinMode(echoright,INPUT);
    //pinMode(IRpin,INPUT);
    pinMode(motorenA, OUTPUT);
    pinMode(motorenB, OUTPUT);
    pinMode(motorin1, OUTPUT);
    pinMode(motorin2, OUTPUT);
    pinMode(motorin3, OUTPUT);
    pinMode(motorin4, OUTPUT);
    //pinMode(sweitchpin,INPUT_PULLUP);
    Serial.begin(9600);


  
 
  kp=1.6;
  //ki=0;
  kd=0;
  // put your setup code here, to run once:

}

double PIDcontroler(double error){
   double proportionalError=error;
  double derrivativeError=0;
   if (dt>0){
   derrivativeError=(error-prevError)/dt;
   }
   prevError=error;
   integralError=integralError+error*dt;

   double output=kp*proportionalError+ki*integralError+kd*derrivativeError;

  return output;
}

void forward(int enAspeed,int enBspeed){
    
    digitalWrite(motorin1,HIGH);
    digitalWrite(motorin2,LOW);
    digitalWrite(motorin3,HIGH);
    digitalWrite(motorin4,LOW);
    analogWrite(motorenA,enAspeed);//left wheel
    analogWrite(motorenB,enBspeed);//right wheel

}

void stop(){
  
    digitalWrite(motorin1,LOW);
    digitalWrite(motorin2,LOW);
    digitalWrite(motorin3,LOW);
    digitalWrite(motorin4,LOW);
    analogWrite(motorenA,0);
    analogWrite(motorenB,0);
}


double distancecal(int trig,int echo){
digitalWrite(trig,LOW);
delayMicroseconds(2);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);

unsigned long duration=pulseIn(echo,HIGH);
if (duration==0) return 999.0;
double distance=duration*0.034/2;
return distance;
}

void loop() {
  double currenttime= millis();
  dt=(currenttime-lasttime)/1000.0;
  lasttime=currenttime;
  double leftdistance = distancecal(trigerleft, echoleft);
  double rightdistance = distancecal(trigerright, echoright);
  double frontdistance=distancecal(trigerfront,echofront);
  if (frontdistance<8.0){
      stop();
    }
  

  

  //if (robotstate == 0) {
    
    
  else{
    /*if (actual > sidewallthreshold || actual == 999.0) {
      robotstate = 1; // Wall lost! Switch to State 1
      return;         // Exit the loop early to immediately start State 1
    }*/
    
    currentError=rightdistance-leftdistance;
    double output=PIDcontroler(currentError);
    forward(constrain(basespeedenA-output,0,255),constrain(basespeedenB+output,0,255));
    Serial.print(errormargin);
    Serial.print(",");
    Serial.println(currentError);
    
  }
  //}else {
   //stop();
  //} 



  
  
  



}


