//written for the Arduino uno or compatible
//switch for debug functions
#define DEBUG 1
#define DEBUGA 1
#define DEBUGM 0
#include <Arduino.h> //GNU LGPL Arduino
#include <Wire.h> //GNU LGPL Arduino
#include <MS5611.h> //MIT License, Rob Tillaart
#include <Adafruit_ICM20X.h> //BSD Liscence, Adafruit
#include <Adafruit_ICM20649.h> //BSD Liscence, Adafruit
#include <Adafruit_Sensor.h> //Apache Liscence, Adafruit
#include "../include/megapins.h" //pin table
#include "../include/addr.h" //i2c addresses
#include "../include/v3.hpp" //vector library
#include "ansicodes.hpp" //ANSI terminal control codes
#define USBBAUD 115200
//======== Functions and structs
//======== Debug functions
#if DEBUG == 1
#endif
//======== Objects and constants
MS5611 ms(0x77);
Adafruit_ICM20649 icm;
uint16_t measurement_delay_us = 65535;
v3 lastA, lastV, pos = 0;
float p0, t0 = 0;
float currentAltiude = 0;
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

  //Barometer Setup & initial readings
  bool *b = ms.begin(); //start barometer
  #if DEBUG == 1 
  Serial.println(*b ? "found" : "not found");
  delete b; // b is not used anywhere else. 
  #endif
  if (b == true){
    float *Psum, *Tsum;
    for (int i=0; i<=10; i++){
      //take 10 readings from barometer/altimiter, average, and set gloabal variables
      ms.read(); //get new data
      *Psum += ms.getPressure();
      *Tsum += ms.getTemperature();
    }
    //average
    p0 = *Psum/10;
    t0 = *Tsum/10;
    delete Psum, Tsum; //free memory
  }
  //MISC Setup
  pinMode(LED_BUILTIN, OUTPUT);
}
void loop() {
  digitalWrite(LED_BUILTIN, HIGH);
  //BAROMETER
  int result = ms.read();

  //IMU
  sensors_event_t accel;
  sensors_event_t gyro;
  sensors_event_t temp;
  icm.getEvent(&accel, &gyro, &temp);

  lastA = v3(accel.acceleration);
  lastV = vel;
  #if DEBUG == 1
  #if DEBUGA == 1
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
  #if DEBUGM == 1
  Serial.print(accel.acceleration.x);
  Serial.print("m/s^2\t");
  Serial.print(vel.x);
  Serial.print("m/s\t");
  Serial.print(pos.x);
  Serial.print("m          \r");
  #endif
  #endif
  digitalWrite(LED_BUILTIN, LOW);
}

