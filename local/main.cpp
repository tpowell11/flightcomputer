/*
Purpose: Ground software for model rocketry flight control system
Author: Tom Powell, 2022
System: Rasbperry PI 4 (anything with g++ >=8.3.0)
See wiring.md in the repository root for wiring instructions
*/
#include <bcm2835.h>
#include <wiringPi.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "lib/RadioHead/RHutil/simulator.h"
#include "lib/RadioHead/RadioHead.h"
#include "lib/RadioHead/RHGenericDriver.h"
#include "lib/RadioHead/RHSPIDriver.h"
#include "lib/RadioHead/RH_RF95.h" //! FIXME bad include path
#include "lib/RadioHead/RHReliableDatagram.h" //! FIXME bad include path

RH_RF95 driver();

int main(int argc, const char* argv[] ){
    if(!driver.init()){
        std::cout<<"Failed to Initialize RF95\n";
    }
}
