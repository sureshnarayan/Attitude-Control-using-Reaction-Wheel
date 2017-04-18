#include <Wire.h>
#define Addr 0x1E               // 7-bit address of HMC5883 compass



String inputString = "";     // a string to hold incoming data
float refAngle=180;
double angle=180.0, error=0, errsum=0, preverror = 0, derror = 0;
float kp=8, ki=0.4, kd = 10, sel_flag = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  Serial.begin(9600);
  Wire.begin(12,14);
  
  // Set operating mode to continuous
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
}

void loop() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  // If compass module lies flat on the ground with no tilt,
  // just x and y are needed for calculation
  if(x > 10000) x-=65536;
  if(y > 10000) y-=65536;
  if(z > 10000) z-=65536;
  float  heading=atan2(x, y)/0.0174532925;
  if(heading < 0) heading+=360;
  heading=360-heading; // N=0/360, E=90, S=180, W=270 

  
  angle = heading;
  Serial.print(angle);
  Serial.print('\t');
  error = angle-refAngle;
  
  
  error = ((int(error*100)+18000+36000)%36000-18000)/100.0;
  errsum += error;
  derror = error - preverror;
  preverror = error;
  if(errsum>500){
    errsum=500;
  }
  else if(errsum<-500){
    errsum=-500;
  }

  float pid=kp*error + ki*errsum + kd*derror;
  if(pid>0){
    if(pid>1023){
      pid=1023;
    }
    analogWrite(4,pid);
    analogWrite(5,0);
  }
  else{
    if(pid<-1023){
      pid=-1023;
    }
    analogWrite(5,-1*pid);
    analogWrite(4,0);
  }
  Serial.print(pid);
  Serial.print('\t');
  Serial.println(error);
}

