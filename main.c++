#include "Wire.h"
#include <MPU6050_light.h>
#include <Keyboard.h>

float x = 0;
float y = 0;

int zona_morta = 30 ;
MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  Keyboard.begin();
  
  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while(status!=0){ } 
  
  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  
  mpu.calcOffsets(); // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();
  
  if((millis()-timer)>10){ // print data every 10ms
	Serial.print("X : ");
	Serial.print(mpu.getAngleX());
	Serial.print("\tY : ");
	Serial.print(mpu.getAngleY());
	Serial.print("\tZ : ");
	Serial.println(mpu.getAngleZ());
	timer = millis();  
  }
  
  x = mpu.getAngleX();
  y = mpu.getAngleY();

  if (x > zona_morta){
    Keyboard.press('');
    delay(100);
    Keyboard.release();
  }
  else if (x < -zona_morta){
    Keyboard.press('');
    delay(100);
    Keyboard.release();
  }
  else if (y > zona_morta){
    Keyboard.press('');
    delay(100);
    Keyboard.release();
  }
  else if(y < - zona_morta){
    Keyboard.press('');
    delay(100);
    Keyboard.release();
  }
  delay(300) ;

}
