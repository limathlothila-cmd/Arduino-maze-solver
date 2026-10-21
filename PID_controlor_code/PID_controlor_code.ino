#define pwmout 5
#define analogin A3
double kp,ki,kd;
double dt,lasttime;
double integralError,prevError,currentError;
double PIDcontroler(double error);
 double reference=100.0;



void setup() {
  pinMode(out,OUTPUT);
  pinMode(in,INPUT);
  Serial.begin(9600);
 
  kp=0.5;
  ki=0;
  kd=0;
  // put your setup code here, to run once:

}





double PIDcontroler(double error){
   double proportional=error;
   double derrivative=(error-prevError)/dt;
   prevError=error;
   integralError=IntegralError+error*dt;

   double output=kp*proportional+ki*integralError+kd*derrivative

  return output;
}


void loop() {
  double currentTime= millis();
  dt=(currentTime-lastTime)/1000;
  lastTime=currentTime;
  double actual=map(analogRead(analogin),0,1023,0,255);
  currentError=actual-reference;
  double output=PIDcontroler(currentError)

  analogWrite(pwmout,output);
  Serial.print(reference);
  Serial.print(;);
  Serial.print(actual);
  a


   // put your main code here, to run repeatedly:

}
