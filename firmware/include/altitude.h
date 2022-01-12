/*
Author: Tom Powell
Purpose: Barometric pressure -> altitude conversions
Platform: ATmega with Arduino bootloader/firmware
Build: Platformio
Source: https://physics.stackexchange.com/questions/333475/how-to-calculate-altitude-from-current-temperature-and-pressure,
https://en.wikipedia.org/wiki/Barometric_formula
*/
#include <math.h> 
//CONSTANTS
const float M = 0.0289644; //kg/mol
const float h0 = 0;//m
const float R = 8.3144598;//J/(mol K)
const float g = 9.80665; //m/s
//FUNCTIONS
float k(float t){
  //kelvin conversion
  return t + 273.15;
}
float pa(float p){
  //pascal conversion
  return 100.0 * p;
}
float barometric(float P, float P_b, float T) {
  //returns the altitude in meters given the pressure (mbar) and temperature (C)
  return ((R*k(T)*log(P/P_b))/(-g*M))+h0;
}