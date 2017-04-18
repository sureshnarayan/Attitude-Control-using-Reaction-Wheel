#include <ESP8266WiFi.h>
//#include <ESP8266WiFiAP.h>
//#include <ESP8266WiFiGeneric.h>
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266WiFiScan.h>
//#include <ESP8266WiFiSTA.h>
//#include <ESP8266WiFiType.h>
//#include <WiFiClient.h>
//#include <WiFiClientSecure.h>
//#include <WiFiServer.h>
#include <WiFiUdp.h>


#include <Wire.h>
#define Addr 0x1E               // 7-bit address of HMC5883 compass

void setup() {
  Serial.begin(9600);
  Serial.println();
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
  Serial.print(x);
  Serial.print("   "); 
  Serial.print(y);
  Serial.print("   "); 
  Serial.print(z);
  Serial.print("   "); 
  float  heading=atan2(x, y)/0.0174532925;
  if(heading < 0) heading+=360;
  heading=360-heading; // N=0/360, E=90, S=180, W=270
  Serial.println(heading);  
  delay(100);
}
