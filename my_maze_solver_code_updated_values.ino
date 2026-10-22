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
  const int IRsensor=2;
  //#define switchpin

  volatile bool reached_white=false;

  const float rightgap=7.0;
  const float leftgap=7.0;
  const float sidewallthreshold=22.5;
  const float frontwallthreshold=13.0;

  int basespeedenA=70;//70//56
  int basespeedenB=60;//60//50

  double kp,ki,kd;
  double dt,lasttime;
  double integralError,prevError,currentError;// 0 get assigned to these global variables by default
  double PIDcontroler(double error);
 



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
    pinMode(IRsensor,INPUT);
    attachInterrupt(digitalPinToInterrupt(IRsensor), whitedetected, RISING);
    Serial.begin(9600);

    kp=1.57;
    //ki=0;
    kd=0.5;
    // put your setup code here, to run once:
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

  void turnleft90(){

      
      digitalWrite(motorin1,LOW);
      digitalWrite(motorin2,HIGH);
      digitalWrite(motorin3,HIGH);
      digitalWrite(motorin4,LOW);
      analogWrite(motorenA,80);
      analogWrite(motorenB,80);
      delay(270);
      stop();

  }

  void turnright90(){
      
      digitalWrite(motorin1,HIGH);
      digitalWrite(motorin2,LOW);
      digitalWrite(motorin3,LOW);
      digitalWrite(motorin4,HIGH);
      analogWrite(motorenA,90);
      analogWrite(motorenB,80);
      delay(285);
      stop();

  }


  void turn180(){
    //turn from the righjt side
    
      digitalWrite(motorin1,HIGH);
      digitalWrite(motorin2,LOW);
      digitalWrite(motorin3,LOW);
      digitalWrite(motorin4,HIGH);
      analogWrite(motorenA,80);
      analogWrite(motorenB,100);
      delay(550);
      stop();

  }

  double distancecal(int trig,int echo){
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

void whitedetected(){
  reached_white=!reached_white;
}

  void lefthandmethod(double leftdistance,double frontdistance,double rightdistance){
    if(leftdistance>sidewallthreshold){
      
      forward(basespeedenA,basespeedenB);
      delay(250);//200
      stop();
      delay(300);
      turnleft90();
      forward(basespeedenA,basespeedenB);
      delay(400);//300
      stop();
      delay(300);
      integralError=0.0;
      prevError=0.0;
      currentError=0.0;
      lasttime=millis();

    }
    else if(frontdistance>frontwallthreshold){
      double currenttime= millis();
      dt=(currenttime-lasttime)/1000.0;
     lasttime=currenttime;
     currentError=leftdistance-leftgap;
    double output=PIDcontroler(currentError);
    forward(constrain(basespeedenA-output,0,255),constrain(basespeedenB+output,0,255));
      
    }
    else if(rightdistance>sidewallthreshold){
      stop();
      delay(300);
      turnright90();
      stop();
      delay(300);
      integralError=0.0;
      prevError=0.0;
      currentError=0.0;
      lasttime=millis();
    }else{
      stop();
      delay(300);
      turn180();
      stop();
      delay(300);
      integralError=0.0;
      prevError=0.0;
      currentError=0.0;
      lasttime=millis();
    }

  }

  void righthandmethod(double leftdistance,double frontdistance,double rightdistance){
    if(rightdistance>sidewallthreshold){
      forward(basespeedenA,basespeedenB);
      delay(300);
      stop();
      delay(300);
      turnright90();
      stop();
      delay(300);
      forward(basespeedenA,basespeedenB);
      delay(350);
      integralError=0.0;
      prevError=0.0;
      currentError=0.0;
      lasttime=millis();
    }else if(frontdistance>frontwallthreshold){
      double currenttime= millis();
      dt=(currenttime-lasttime)/1000.0;
     lasttime=currenttime;
     currentError=rightdistance-rightgap;
    double output=PIDcontroler(currentError);
    forward(constrain(basespeedenA+output,0,255),constrain(basespeedenB-output,0,255));
    }else if(leftdistance>sidewallthreshold){
      stop();
      delay(300);
      turnleft90();
      stop();
      delay(300);
      integralError=0.0;
      prevError=0.0;
      currentError=0.0;
      lasttime=millis();
    }else{
      stop();
      delay(200);
      turn180();
      stop();
      delay(300);
      integralError=0.0;
      prevError=0.0;
      currentError=0.0;
      lasttime=millis();
    }

  }

  void loop() {
    double leftlength= distancecal(trigerleft,echoleft) ;
    double frontlength= distancecal(trigerfront,echofront) ;
    double rightlength= distancecal(trigerright,echoright) ;
    //int IRvalue=digitalRead(IRpin);
    //int switchstate=digitalRead(switchpin);


    /*if (IRvalue==LOW){
      stop();
      while(true){
        delay(1000);
      }
    }*/

    /*if (switchstate==HIGH){}
      righthandmethod(leftlength,frontlength,rightlength);
    }else{
      lefthandmethod(leftlength,frontlength,rightlength);
    }*/

    //lefthandmethod(leftlength,frontlength,rightlength);
    //righthandmethod(leftlength,frontlength,rightlength);
    if(!reached_white){
      lefthandmethod(leftlength,frontlength,rightlength);
    }
    else{
      stop();
    }

  }
