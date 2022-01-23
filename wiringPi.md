# Raspberry PI RF95 Wiring
This document describes how to connect the RF95 module to the Raspberry Pi.
This wiring applies to any RF module that follows the same pinout.
The only thing to note about the below table is that the `EN` pin on the RF95
*MUST* be left floating, or else the modules will fail to initialize.
```
RF95     PI
G0 -----
SCK ---- SCLK
MISO
MOSI
RST
Vin --- 3V3
GND --- GND
```
