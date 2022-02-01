/*
Author: Tom Powell 2022
Purpose: Message formating utility functions for RH_RF95
Platform: AVR (via Platformio)
*/
#ifndef MESSAGE_H
#define MESSAGE_H

#include <Arduino.h>

void chartouint(char * what, size_t len, uint8_t * where){
    for(int i; i < len; i++){
        //convert each element of what into uint
        where[i] = (uint8_t) what[i];
    }
}
uint8_t chartouint(char what){
    return (uint8_t) what;
}
int lastNZIndex (uint8_t * what, size_t len) {
    for( int i; i < len; i++){
        if( what[i] != 0){
            return i; 
        } else {
            continue;
        }
    }
}
void msgConcat (uint8_t * message, uint8_t * what, size_t len){
    ip = lastNZIndex(&message)
}
#endif