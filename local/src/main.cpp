/*
Author: Tom Powell
Purpose: Ground firmware for flight controller project
*/
#include <SPI.h> //needed for lorawan 
#include <RH_RF95.h> //GPL Liscence, AirSpayce Ltd. 
#include <RHEncryptedDriver.h> //GPL Liscence, AirSpayce Ltd.
#include <Arduino.h> //GNU LGPL Arduino
#include <Speck.h>

#include "conf.hpp" //local configuration file
RH_RF95 lora(3, 2); //init of rfm95w
Speck Cipher;
RHEncryptedDriver enc(lora, Cipher); // Instantiate the driver with those two
int snr;

void setup() {
    delay(4000); //allow Serial connect before running
    bool r = lora.init(); //start rfm95w
    Serial.println(r ? "lora ok" : "lora fail");
    lora.setFrequency(LORA_FREQ); //set frequency
    lora.setTxPower(LORA_POWER); //set lora power
    lora.setModeRx();
    Cipher.setKey(encryptkey, 16);

}

void loop() {
    if(enc.available()){
        uint8_t msgBuf[enc.maxMessageLength()];
        uint8_t msgLen;
        if(enc.recv(msgBuf, &msgLen)) {
            Serial.println((char*) &msgBuf);
        } else {
            Serial.println("Recive Fail");
        }
    }
}