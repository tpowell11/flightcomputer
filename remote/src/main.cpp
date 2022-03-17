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
#include <ArduinoJson.h>
//project specific headers
#include "../include/megapins.h" //pin table
#include "../include/addr.h" //i2c addresses
#include "../include/v3.hpp" //vector library
#include "../include/altitude.h" //pressure -> altitude conversion
#include "../params.h" //flight parameter file

#define USBBAUD 9600
////////////////FUNCTIONS////////////////

//======== Debug functions
#if DEBUG == 1
#endif
////////////////RADIO OBJS////////////////
RH_RF95 lora(rf_cs, rf_irq); //init of rfm95w
Speck cipher;
RHEncryptedDriver driver(lora,cipher);
const int msgLen = 251;
uint8_t data[msgLen+1];
uint8_t rbuf[RH_RF95_MAX_MESSAGE_LEN];
uint8_t rbuf_s;
StaticJsonDocument<msgLen> doc;
////////////////SENSOR OBJS////////////////
MS5611 ms(0x77);
Adafruit_ICM20649 icm;
uint16_t measurement_delay_us = measurementDel;

////////////////IMU CALC VARS////////////////
float imudel_s = 0.065535;
v3 lastacc, lastvel, pos, vel, acc = 0;
float p0, t0, alt, p, t = 0;
char tempMsg[msgLen];
//======== Application loop
void setup() {
  Wire.begin(); //start i2c
  #if DEBUG == 1
  Serial.begin(USBBAUD);
  Serial.println("Began Init");
  //while(!Serial) ; //wait for serial start
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
    Serial.println("LORA has not initialized");
  }
  Serial.println("LORA Initialized, Coninuing");
  lora.setFrequency(freq); //freq from params.h
  lora.setTxPower(power); //power from params.h
  lora.setModemConfig(RH_RF95::ModemConfigChoice::Bw125Cr48Sf4096);
  cipher.setKey(key,16); //key from params.h
  ////////////////BAROMETER SETUP////////////////
  bool b = ms.begin(); //start barometer
  if (b == true){
    #if DEBUG == 1
    Serial.println("Getting Atmospheric Data");
    #endif
    float Psum, Tsum;
    for (int i=0; i<=averageCycles; i++){
      ms.read(); //get new data
      Psum += ms.getPressure();
      Tsum += ms.getTemperature();
    }
    //average
    p0 = Psum/averageCycles;
    t0 = Tsum/averageCycles;
    //delete Psum;
    //delete Tsum; //free memory
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
    t=ms.getTemperature();
    alt = barometric(p,p0,t);
  }
  //sprintf(tempMsg,"%f", p);
  //strcat(tempMsg, msg);
  //IMU
  sensors_event_t accel, gyro, temp;
  icm.getEvent(&accel, &gyro, &temp);
  acc = v3(accel);
  vel = integrate(lastacc,acc,imudel_s);
  pos = integrate(lastvel, vel,imudel_s);
  lastacc = acc;
  lastvel = vel;
  doc["ax"] = acc.x;
  doc["ay"] = acc.y;
  doc["az"] = acc.z;
  //Transmit and receive
  serializeJson(doc,data);
  for(auto i : data){
    Serial.print(i);
    Serial.print(",");
  }
  Serial.println((char*)data);
  Serial.println();
  driver.send(data,256);
  /* sizeof returns the number of BYTES of a type, not the number of BITS.
  not entirely sure why that matters though.
  sizeof(char) = 1 on this platform, apparently. 
  * Refactored to use msgLen for maintainability 
  */
  driver.waitPacketSent();
  driver.waitCAD();
  delay(1000);
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
    Serial.print(t);
    Serial.print("\nP:");
    Serial.println(p);
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