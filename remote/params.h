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
#define DEBUGLORA 1
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
/* The key must be the same between the server (here) and the client.
The frequency must also be the same.
*/
const char key[16] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; 
const float freq = 915;//Mhz
const int power = 13; //range from 1-23

//DATA COLLECTION PARAMETERS
const int measurementDel = 65535;

///////////////////////////////////////////////////////////
//Startup Parameters

//Number of measuements to average on startup
const int averageCycles = 10;

//
