//written for the Arduino uno or compatible
// Arduino default libraries
#include <Arduino.h> //GNU LGPL Arduino
#include <Wire.h> //GNU LGPL Arduino
#include <SPI.h> //needed for lorawan
//Altimiter Interface
#include <MS5611.h> //MIT License, Rob Tillaart
//Adafruit Sensor
#include <Adafruit_ICM20X.h> //BSD Liscence, Adafruit
#include <Adafruit_ICM20649.h> //BSD Liscence, Adafruit
#include <Adafruit_Sensor.h> //Apache Liscence, Adafruit
//Radio interfacing
#include <RH_RF95.h> //GPL Liscence, AirSpayce Ltd.
#include <RHEncryptedDriver.h> //security driver
#include <Speck.h> //encryption
//project specific headers
#include "../include/megapins.h" //pin table
#include "../include/addr.h" //i2c addresses
#include "../include/v3.hpp" //vector library
#include "../include/altitude.h" //pressure -> altitude conversion
#include "../params.h" //flight parameter file
#include "ansicodes.hpp" //ANSI terminal control codes
#define USBBAUD 115200
////////////////FUNCTIONS////////////////

//======== Debug functions
#if DEBUG == 1
#endif
////////////////RADIO OBJS////////////////
RH_RF95 lora(rf_cs, rf_irq); //init of rfm95w
Speck cipher;
RHEncryptedDriver driver(lora,cipher);
const int msgLen = 256;
char msg[msgLen] = "";
////////////////SENSOR OBJS////////////////
MS5611 ms(0x77);
Adafruit_ICM20649 icm;
uint16_t measurement_delay_us = measurementDel;

////////////////IMU CALC VARS////////////////
float imudel_s = 0.065535;
v3 lastacc, lastvel, pos, vel, acc = 0;
float p0, t0, alt, p, temp = 0;
//======== Application loop
void setup() {
  Wire.begin(); //start i2c
  #if DEBUG == 1
  Serial.begin(USBBAUD);
  #endif
  ////////////////IMU SETUP////////////////
  icm.begin_I2C(ADDR::ICM); //without this the chip wont start. lazy bastard
  icm.setAccelRange(ICM20649_ACCEL_RANGE_30_G); //set to 30G range
  icm.setGyroRange(ICM20649_GYRO_RANGE_2000_DPS); //2000 deg/sec range

  ////////////////LORWAN CONFIG//////////////// 
  /* This rather verbose method of resetting the radio comes from
  https://forum.arduino.cc/t/radiohead-library-and-rfm95-weird-init-issues/389054/3
  and was implemented here to combat some issues with the RH_RF::init().
  Turned out that the enable pin (EN) could not be connected to ground.
  Rather than remove this code, it was left here because there is no
  such thing as being too careful.
  */
  pinMode(4,OUTPUT);
  digitalWrite(4,LOW);
  delayMicroseconds(100);
  pinMode(4,INPUT);
  #if DEBUG==1
  Serial.println("LORA Reset");
  #endif
  delayMicroseconds(100);
  while(!lora.init()){
    delay(100);
  }
  lora.setFrequency(freq); //freq from params.h
  lora.setTxPower(power); //power from params.h

  ////////////////BAROMETER SETUP////////////////
  bool b = ms.begin(); //start barometer
  if (b == true){
    float *Psum, *Tsum;
    for (int i=0; i<=averageCycles; i++){
      ms.read(); //get new data
      *Psum += ms.getPressure();
      *Tsum += ms.getTemperature();
    }
    //average
    p0 = *Psum/averageCycles;
    t0 = *Tsum/averageCycles;
    delete Psum;
    delete Tsum; //free memory
  }

  ////////////////MISCELLANEOUS////////////////
  pinMode(LED_BUILTIN, OUTPUT);
  #if DEBUG == 1
  Serial.println(b ? "alt ok" : "alt fail");
  //Serial.println(r ? "lora ok" : "lora fail");
  #endif
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  //BAROMETER
  int result = ms.read();
  if (result == 0){
    p=ms.getPressure();
    temp=ms.getTemperature();
    alt = barometric(p,p0,temp);
  }
  sprintf(msg,"%f", p);

  //IMU
  sensors_event_t accel, gyro, temp;
  icm.getEvent(&accel, &gyro, &temp);
  acc = v3(accel);
  vel = integrate(lastacc,acc,imudel_s);
  lastacc = acc;
  lastvel = vel;
  
  //Transmit and recive
  uint8_t data[msgLen+1] = {0}; //allow extra charachter for terminator?
  for(uint8_t i = 0; i<= msgLen; i++) data[i] = (uint8_t)msg[i]; //convert each char of msg to uint8_t
  driver.send(data,sizeof(data));

  #if DEBUG == 1
  #if DEBUGALT == 1
  if (result != MS5611_READ_OK)
  {
    Serial.print("Error in read: ");
    Serial.println(result);
  }
  else
  {
    Serial.print("T:");
    Serial.print(ms.getTemperature(), 2);
    Serial.print("\nP:");
    Serial.println(ms.getPressure(), 2);
  }
  #endif
  #if DEBUGIMU == 1
  acc.to_str("m/s2\n");
  vel.to_str("m/s\n");
  pos.to_str("m\n");
  #endif
  #endif
  digitalWrite(LED_BUILTIN, LOW);
}
