/*
Purpose: Ground software for model rocketry flight control system
Author: Tom Powell, 2022
System: Rasbperry PI 4 (anything with g++ >=8.3.0)
*/
#include <bcm2835.h>
#include <iostream>
#include <ctime>
#include <vector>
#include <string>
#include "../remote/.pio/libdeps/megaatmega2560/RadioHead/RH_RF95.h" //! FIXME bad include path
#include "../remote/.pio/libdeps/megaatmega2560/RadioHead/RHReliableDatagram.h" //! FIXME bad include path
