#include "I2C.h"
#define ACC 0x1C
int m=16;
void setup() 
{
  I2c.begin();

  Serial.begin(9600);

  pinMode(8,OUTPUT);
  digitalWrite(8,0); 
  pinMode(9,OUTPUT);
  digitalWrite(9,0);
  pinMode(10,OUTPUT);
  digitalWrite(10,0);
  pinMode(11,OUTPUT);
  digitalWrite(11,0);
} 
void loop() 
{ 
  I2c.read(ACC,0x0B,1) ;
  I2c.write(ACC,0x2A,0x03); //to start 8-bit mode

  /*X Register*/
  I2c.read(ACC,0x01,1);
  byte X = I2c.receive();
  X=map(X,0,255,0,m);
  /*Y Register*/
  I2c.read(ACC,0x03,1); 
  byte Y = I2c.receive(); 
  Y=map(Y,0,255,0,m);
  /*z Register*/
  I2c.read(ACC,0x05,1); 
  byte Z = I2c.receive(); 
  Z=map(Z,0,255,0,m);

  Serial.print(X);  //serial print
  Serial.print(" ");
  Serial.print(Y);
  Serial.print(" ");
  Serial.print(Z);
  Serial.println(" ");

  /*+x*/
  if((X>=2 && X<=7))
  {
    if((Y==0 || Y==16 || Y==15 || Y==1))/*forward*/
    {
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
    else if((Y>=11 && Y<=14))/*forward left*/
    {
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    else if((Y>=2 && Y<=7))/*forward right*/
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
  }
  /*-x*/
  else if((X>=11 && X<=14))
  {
    if((Y==0 || Y==16 || Y==15 || Y==1))/*backward*/
    {
      digitalWrite(8,0);
      digitalWrite(9,0);
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
    else if((Y>=11 && Y<=14))/*backward left*/
    {
      digitalWrite(8,0);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
    else if((Y>=2 && Y<=7))/*backward right*/
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
  }
  /*+y*/
  else if((Y>=2 && Y<=7))
  {
    if((X==0 || X==16 || X==15 || X==1))/*right*/
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    else if((X>=11 && X<=14))/*backward right*/
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,1);
      digitalWrite(11,0);
    }
    else if((X>=2 && X<=7))/*forward right*/
    {
      digitalWrite(8,1);
      digitalWrite(9,0);
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
  }
  /*-Y*/
  else if((Y>=11 && Y<=14))
  {
    if((X==0 || X==16 || X==15 || X==1))/*left*/
    {
      digitalWrite(8,0);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
    else if((X>=11 && X<=14))/*backward left*/
    {
      digitalWrite(8,0);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,1);
    }
    else if((X>=2 && X<=7))/*forward left*/
    {
      digitalWrite(8,1);
      digitalWrite(9,1);
      digitalWrite(10,0);
      digitalWrite(11,0);
    }
  }
  else
  {
    digitalWrite(8,0);
    digitalWrite(9,0);
    digitalWrite(10,0);
    digitalWrite(11,0);
  }
}



