#include "Adafruit_DRV2605.h"

Adafruit_DRV2605 drv;

int muscleInput = A0;
int ledPin = 13;
int muscleValue = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(muscleInput, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  drv.begin();
  drv.setMode(DRV2605_MODE_INTTRIG);
  drv.selectLibrary(1);  
}

void loop() 
{  
 switch(CollectSerialData())
 {
  case 0:
  {
    break;
  }  
  
  case 1:
  {
    LedOn();
    break;
  } 
  
  case 2:
  {
    LedOff();
    break;
  }  
  
  case 3:
  {
    MotorOn();
    break;
  }  
  
  case 4:
  {
    break;
  }
   
  case 5:
  {
    CollectMuscleData();
    Serial.println(muscleValue);
    delay(20);
    break;
  }

  case 6:
  {    
    break;
  }
   
  default:
  {
    break;
  }  
 }
}

void CollectMuscleData()
{
  muscleValue = analogRead(muscleInput);
}  

void LedOn()
{
  digitalWrite(ledPin, HIGH);
}

void LedOff()
{
  digitalWrite(ledPin, LOW);
}

void MotorOn()
{
  int j;
  for(int i=0;i<4;i++)
  {
    drv.setWaveform(i, 44);
    j=i;
  }
  drv.setWaveform(j,0);
  drv.go();  
}

void MotorOff()
{
  drv.setWaveform(0, 0);  
}

byte CollectSerialData()
{
  if(Serial.available() > 0)
  {
    return Serial.read();
  }
}
