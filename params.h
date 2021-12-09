/*
Author: Tom Powell
Purpose: Auto-generated file to hold system run parameters
Platform: ATmega with Arduino bootloader/firmware
Build: Platformio
*/
//M.K.S UNITS
#define DEBUG 1
#define DEBUGALT 1
#define DEBUGIMU 1
///////////////////////////////////////////////////////////
//Deployment & general run params

//WAIT FOR AFTER APOGEE FOR DEPLOYMENT
const bool waitAfterAppogee = true;

//PARACHUTE A DEPLOYMENT PARAMETERS
const float deployAltitudeA = 1000;

//PARACHUTE B DEPLOYMENT PARAMETERS
const float deployAltitudeB = 700;

//IMU CALIBRATION CONSTANTS
const float ccstX = 0;
const float ccstY = 0;
const float ccstZ = -10;

//BAROMETER CALIBRATION CONSTANTS
const float ccstBar = 0;
const float ccstTem = 0;

//LoRaWAN CONFIGURATION CONSTANTS
const char SelfIp[16] = "255.255.255.255";
const char TargetIp[16] = "255.255.255.255";
const int freq = 915;//Mhz

//DATA COLLECTION PARAMETERS
const int measurementDel = 65535;

///////////////////////////////////////////////////////////
//Startup Parameters

//Number of measuements to average on startup
const int averageCycles = 10;

//