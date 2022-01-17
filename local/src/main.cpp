/*
Author: Tom Powell
Purpose: Ground firmware for flight controller project
*/
#include <SPI.h> //needed for lorawan 
#include <RH_RF95.h> //GPL Liscence, AirSpayce Ltd. 
#include <Arduino.h> //GNU LGPL Arduino

RH_RF95 lora(3, 2); //init of rfm95w


void setup() {
    bool r = lora.init(); //start rfm95w
    Serial.println(r ? "lora ok" : "lora fail");
    
}

void loop() {

}