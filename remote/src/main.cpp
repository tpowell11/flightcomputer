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
#include <RHEncryptedDriver.h> //security
#include <Speck.h>
//project specific headers
#include "../include/megapins.h" //pin table
#include "../include/addr.h" //i2c addresses
#include "../include/v3.hpp" //vector library
#include "../include/altitude.h" //pressure -> altitude conversion
#include "../params.h" //flight parameter file
#include "ansicodes.hpp" //ANSI terminal control codes
#define USBBAUD 115200
//======== Functions and structs
//======== Debug functions
#if DEBUG == 1
#endif
//======== Objects and constants
MS5611 ms(0x77);
RH_RF95 lora(rf_cs, rf_irq); //init of rfm95w
//RHEncryptedDriver driver(lora,) //decide on encryption algorithim
Adafruit_ICM20649 icm;
uint16_t measurement_delay_us = measurementDel;
float imudel_s = 0.065535;
v3 lastacc, lastvel, pos, vel, acc = 0;
float p0, t0, alt, p, temp = 0;
//======== Application loop
void setup() {
  #if DEBUG == 1
  Serial.begin(USBBAUD);
  #endif
  Wire.begin(); //start i2c
  //IMU Setup
  icm.begin_I2C(ADDR::ICM); //without this the chip wont start. lazy bastard
  icm.setAccelRange(ICM20649_ACCEL_RANGE_30_G); //set to 30G range
  icm.setGyroRange(ICM20649_GYRO_RANGE_2000_DPS); //2000 deg/sec range
  //Lora init
  // Use code from raspi desktop "rf95_client"

  bool r = lora.init(); //start rfm95w
  //Barometer Setup & initial readings
  bool b = ms.begin(); //start barometer
  if (b == true){
    float *Psum, *Tsum;
    for (int i=0; i<=averageCycles; i++){
      //take 10 readings from barometer/altimiter, average, and set gloabal variables
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
  //MISC Setup
  pinMode(LED_BUILTIN, OUTPUT);
  #if DEBUG == 1
  Serial.println(b ? "alt ok" : "alt fail");
  Serial.println(r ? "lora ok" : "lora fail");
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

  //IMU
  sensors_event_t accel, gyro, temp;
  icm.getEvent(&accel, &gyro, &temp);
  acc = v3(accel);
  vel = integrate(lastacc,acc,imudel_s);
  lastacc = acc;
  lastvel = vel;


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
