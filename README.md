

# libpynq-expanded

Additions to the TU/e libpynq library.
Most come with a small example program.

## Overview

 - vl53l0x: Adds driver for the VL53L0X TOF Distance sensor ([Adapted From here](https://github.com/bitbank2/VL53L0X))
 - tca9548a: Adds driver for the TCA9548a I2C multiplexer to resolve the address conflict between the TCS3472 AND VL53L0X
 - tcs3472: Adds driver for the TCS3472 Colour Sensor
 - PULSECOUNTER: Add an example usages for this existing library.
 - MQTT_UART: Demonstrates interactions between PYNQ and 5EID0 UART<>MQTT bridge.


## How to use:
All additions are located in the `libary` folder of the Git Repo.  

**To quickly use an addition follow the quick procedure.**  
 The library folder procedure is how you make the addition available to all programs in the `applications` folder, not just the one. (It saves a lot of copy pasting in the long run!)
 
 ### A: Quick And Easy:
Every folder contains an independent addition, simple copy the `.c` and `.h` files for the needed additions besides your `main.c` into the directory your working in. e.g `applications/small-test/`on the PYNQ and add the related `#include "name-of-header.h>"` for every `.h` file you added. 

#### Example:

![Clean Folder](https://raw.githubusercontent.com/Walthzer/libpynq-expanded/master/assets/images/clean-folder.PNG "Clean Folder")

After adding the VL53LOX files:

![Added Folder](https://raw.githubusercontent.com/Walthzer/libpynq-expanded/master/assets/images/added-folder.PNG "Added Folder")

### B: Into Library Folder:
Copy the `.c` and `.h` files in to the `library` folder in the libpynq and run `make install` as you would on when you first install libpynq. now you simply `#include <name-of-header.h>` as you would e.g `#include <libpynq.h>` to use the relevant addition.
