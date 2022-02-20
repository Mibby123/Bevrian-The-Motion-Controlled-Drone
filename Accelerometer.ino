#include<Wire.h>
#include <math.h>
const int MPU = 0x68;
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;      

#define forward 12
#define back 11
#define right 10
#define left 9
#define up 8
#define down 7


void setup() {
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);
  pinMode(forward, OUTPUT);
  pinMode(back, OUTPUT);
  pinMode(right, OUTPUT);
  pinMode(left, OUTPUT);
  pinMode(up, OUTPUT);
  pinMode(down, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);

  int AcXoff, AcYoff, AcZoff, GyXoff, GyYoff, GyZoff;
  int temp, toff;
  double t, tx, tf;

  //Acceleration data correction
  AcXoff = -950;
  AcYoff = -300;
  AcZoff = 0;

  //read accel data
  AcX = (Wire.read() << 8 | Wire.read()) + AcXoff;
  AcY = (Wire.read() << 8 | Wire.read()) + AcYoff;
  AcZ = (Wire.read() << 8 | Wire.read()) + AcYoff;

  digitalWrite(forward,LOW);
  digitalWrite(back,LOW);
  digitalWrite(left,LOW);
  digitalWrite(right,LOW);
  digitalWrite(up,LOW);
  digitalWrite(down,LOW);

  if (AcX > 2000){
    digitalWrite(forward,HIGH); 
    digitalWrite(back, LOW); 
  }
  if (AcX < -2000){
    digitalWrite (back,HIGH);
    digitalWrite (forward,LOW);
  }
  if (AcY > 2000){
    digitalWrite(left,HIGH); 
    digitalWrite(right, LOW); 
  }
  if (AcY < -2000){
    digitalWrite (right,HIGH);
    digitalWrite (left,LOW);
  }
  if (AcZ > 2000){
    digitalWrite(up,HIGH); 
    digitalWrite(down, LOW); 
  }
  if (AcZ < -2000){
    digitalWrite (down,HIGH);
    digitalWrite (up,LOW);
  }

  
  delay(333);
}
