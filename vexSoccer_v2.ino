#include <Wire.h>
int err;
const int addr = 0x10 >> 1;
const float pi = 3.14159;


int mux(byte channel) {
  byte controlRegister = 0x04;
  controlRegister |= channel;
  Wire.beginTransmission(0x70);
  if (channel == 0xFF) {
    Wire.write(0x00);  //deselect all channels
  }
  else {
    Wire.write(controlRegister);  //set to selected channel
  }
  return Wire.endTransmission();
}

int ir(float *zone, float *Max)
{
  *Max=-1;
  Wire.beginTransmission(addr);
  Wire.write(0x49);
  int result = Wire.endTransmission();
  int bytes = Wire.requestFrom(addr,6);
  if(bytes == 6){
    *zone = Wire.read();
    for(int i=1;i<bytes;i++){
      int val=Wire.read();
      if(val>*Max)
        *Max=val;
    }
   }
    return err;
}

void motor(int hex, unsigned char percent)
{
  //unsigned char speed = 128* (percent / 100);
  Wire.beginTransmission(hex >> 1);
  Wire.write(0x2A);
  Wire.write(percent);
  int err3 = Wire.endTransmission();
  Serial.println(err3);

  delayMicroseconds(100);
  Wire.beginTransmission(hex >> 1);
  Wire.write(0x28);
  Wire.write(0x05);
  int err4 = Wire.endTransmission();
  Serial.println(err4);
}

void follow(float degree){
   float rad = degree/(180/pi); 
   int FLSpeed = (-(sin(rad)*100)*(sqrt(3)/2)) - ((cos(rad)*100)/2); // front-left
   int FRSpeed  = (sin(rad)*100)*sqrt(3)/2 - (cos(rad)*100)/2; // front-right
   int BSpeed = (cos(rad)*100);

   motor(0x20, FLSpeed);
   motor(0x22, FRSpeed);
   motor(0x24, BSpeed);
}

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  /*float leftZone;
  float leftInt;
  float rightZone;
  float rightInt;
  float zoneAvg;
  mux(1);
  
  int error=ir(&leftZone, &leftInt);
  delay(500);
  mux(2);

  error=ir(&rightZone,&rightInt);
  Serial.println(rightZone); 
  Serial.println(leftZone);

  zoneAvg = (leftZone + rightZone)/2;
  Serial.println(zoneAvg);
  Serial.println("-----------");
  delay(50);
  float deg = (zoneAvg - 2)*30;
  follow(deg);
  */

   motor(0x20, 100);
   motor(0x22, 100);
   motor(0x24, 100);
}
