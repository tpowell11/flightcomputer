/*
Author: Tom Powell
Purpose: Human-readable remote error table
*/
#include <stdint.h>
typedef uint8_t err_t;

//Flight events
err_t EV_RDY_LAUNCH = 0;
err_t EV_C1_DEPL = 1;
err_t EV_C2_DEPL = 2;
err_t EV_LANDING  = 3;

//On-PCB communication errors
err_t ERR_IMU_COMM = 4;
err_t ERR_BAR1_COMM = 5;
err_t ERR_BAR2_COMM = 6;
err_t ERR_MAG_COMM = 7;
err_t ERR_GPS_COMM = 8;

//Mechanical errors
err_t ERR_DEPL_C1 = 9;
err_t ERR_DEPL_C2 = 10;
err_t ERR_LOW_VOLT = 11;
err_t ERR_HIGH_VOLT = 12;

//Range errors
err_t ERR_BAR1_RANGE = 13;
err_t ERR_BAR2_RANGE = 14;
err_t ERR_IMU_RANGE = 15;
err_t ERR_MAG_RANGE = 16;

//Misc. errors
err_t ERR_GPS_NOLOCK = 17;