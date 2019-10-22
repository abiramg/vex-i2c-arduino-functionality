#include <Wire.h>

int err;

//vex sends all call; i2c bus activity
void allCall(){
  Wire.beginTransmission(0x00); //general call address
  Wire.write(0x4E);
  Wire.write(0xCA);
  Wire.write(0x03);
  err = Wire.endTransmission();
  
  if(err != 0){
    Serial.println("error in all call: ");
    Serial.print(err);
    delay(10);
  }
}

//initializes sensor; sends wakeup pulse to sensor
void initializeSensor(char pinNum, char add) {
  pinMode(pinNum, OUTPUT);
  int check;
  
  digitalWrite(pinNum, HIGH);
  delay(5);

  digitalWrite(pinNum,LOW); //pulse
  delayMicroseconds(107);
  digitalWrite(pinNum, HIGH);
  
  do
  {
    check = Wire.requestFrom(0x60 >>1, 1);
    Wire.read();
    Serial.println("Checking initialization of Sensor" );
    Serial.print(pinNum);
  } while(check !=1);

  Wire.beginTransmission(0x60 >> 1);
  Wire.write(0x4D); //changes address
  Wire.write(add);
  err = Wire.endTransmission();
  if(err != 0){
    Serial.println("error with Sensor " );
    Serial.print(pinNum);
    Serial.print(" initialization: ");
    Serial.print(err);
    delay(10);
  }
}

void setup() {


}

void loop() {
  // put your main code here, to run repeatedly:

}
