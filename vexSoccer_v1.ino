#include <Wire.h>

const int addr = 0x10 >> 1;


int ir()
{

  Wire.beginTransmission(addr);
  Wire.write(0x49);
  int result = Wire.endTransmission();
  int value = Wire.requestFrom(addr, 1);
  int posit;
  if (value == 1)
  {
    return (Wire.read());
  }
  else
  {
    return 5;
  }
  
}

int irIntensity()
{
  int sumInt = 0;
  Wire.beginTransmission(addr);
  Wire.write(0x49);
  int result = Wire.endTransmission();
  int value = Wire.requestFrom(addr, 6);
  int posit;
  if (value == 6)
  {
    Wire.read();
    for (int i = 1; i < 6; i++)
    {
      sumInt += Wire.read();
    }
    return sumInt;
  }
  return 0;
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

void forward()
{
  motor(0x20, 0);
  motor(0x22, 127);
  motor(0x24, -127);
}

void rside()
{
  motor(0x20, 0x54);
  motor(0x22, 0xD4);
  motor(0x24, 0xD4);
}

void lside() {
  motor(0x20, 0xAA);
  motor(0x22, 0x2A);
  motor(0x24, 0x2A);
}

void backward()
{
  motor(0x20, 0);
  motor(0x22, -127);
  motor(0x24, 127);
}

void ldiag()
{
  motor(0x20, 0x80);
  motor(0x22, 0x7E);
  motor(0x24, 0x00);

}

void rdiag() {
  motor(0x20, 0x7E);
  motor(0x22, 0x00);
  motor(0x24, 0x80);
}

void setup() {
  //Wire.setClock(10000);

  Serial.begin(9600);
  Wire.begin();

  Serial.println("Open");

  delay(5);

  Wire.beginTransmission(0x00);
  Wire.write(0x4E);
  Serial.println("Write 1");
  Wire.write(0xCA);
  Serial.println("Write 2");
  Wire.write(0x03);
  Serial.println("Write 3");
  delay(50);
  int err1 = Wire.endTransmission();

  Serial.println("device int");
  Serial.println(err1);
  delayMicroseconds(2257);

  Serial.println("Clear");

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  digitalWrite(10, LOW);
  delayMicroseconds(107);
  digitalWrite(10, HIGH);


  int nb = Wire.requestFrom(0x60 >> 1, 1);
  Serial.println(nb);


  Wire.beginTransmission(0x60 >> 1);
  Wire.write(0x4D);
  Wire.write(0x20);
  int err2 = Wire.endTransmission();
  Serial.println(err2);



  //second motor

  pinMode(11, OUTPUT);
  digitalWrite(11, HIGH);
  delay(5);

  digitalWrite(11, LOW);
  delayMicroseconds(107);
  digitalWrite(11, HIGH);


  nb = Wire.requestFrom(0x60 >> 1, 1);
  Serial.println(nb);


  Wire.beginTransmission(0x60 >> 1);
  Wire.write(0x4D);
  Wire.write(0x22);
  err2 = Wire.endTransmission();
  Serial.println(err2);

  //third motor

  pinMode(12, OUTPUT);
  digitalWrite(12, HIGH);
  delay(5);

  digitalWrite(12, LOW);
  delayMicroseconds(107);
  digitalWrite(12, HIGH);


  nb = Wire.requestFrom(0x60 >> 1, 1);
  Serial.println(nb);


  Wire.beginTransmission(0x60 >> 1);
  Wire.write(0x4D);
  Wire.write(0x24);
  err2 = Wire.endTransmission();
  Serial.println(err2);

  /* motor(0x20, 100);
    motor(0x22, 100);
    motor(0x24, 100);*/
  //side();

}

void loop() {
 Wire.beginTransmission(0x20 >> 1);
  Wire.write(0x2A);
  Wire.write(128);
  int err3 = Wire.endTransmission();
  Serial.println(err3);

  delayMicroseconds(100);
  Wire.beginTransmission(0x20 >> 1);
  Wire.write(0x28);
  Wire.write(0x05);
  int err4 = Wire.endTransmission();
  Serial.println(err4);
 
 /* int dir;
  int inten = irIntensity();
  while (inten < 180) {
    dir = ir();
    if (inten > 180)
    {
      forward();
    }
    else if (dir == 5) {
      forward();
    }
    else if (dir > 5 && dir < 7) {
      ldiag();
    }
    else if (dir < 5 && dir > 3) {
      rdiag();
    }
    else {
      backward();
    }
    inten = irIntensity();
  }

*/}

