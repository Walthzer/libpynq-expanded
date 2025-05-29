/*
 * tca9548a_example.c
 *
 * Minimal example demonstrating how to use the TCA9548A I2C multiplexer
 * with the libpynq platform. This code shows how to initialize the I2C
 * interface, configure the multiplexer, and select different channels to
 * communicate with multiple I2C devices on the same bus.
 *
 * Author: Meltedgyro_FPV
 * License: GNU General Public License v3.0 or later
 */

#include <stdio.h>
#include <iic.h>
#include <switchbox.h>
#include "TCA9548A.h"

int main(void) {
    // === Step 1: Connect physical I2C pins to IIC0 hardware block ===
    switchbox_set_pin(IO_AR_SCL, SWB_IIC0_SCL); // Map SCL line to IIC0 controller
    switchbox_set_pin(IO_AR_SDA, SWB_IIC0_SDA); // Map SDA line to IIC0 controller

    // === Step 2: Initialize I2C controller (IIC0) ===
    iic_init(IIC0);

    // === Step 3: Declare and initialize the multiplexer handle ===
    tca9548a mux;
    if (tca9548a_init(IIC0, &mux)) {
        fprintf(stderr, "Failed to initialize TCA9548A multiplexer\n");
        iic_destroy(IIC0);
        return 1;
    }

    // === Step 4: Select a specific channel on the multiplexer ===
    // Channel 0 might be used for a color sensor or another I2C device
    if (tca9548a_select_channel(&mux, 0)) {
        fprintf(stderr, "Failed to select channel 0 on multiplexer\n");
    } else {
        printf("✔ Channel 0 selected — ready to talk to device on channel 0.\n");
        // Here, you would call the device driver functions for your sensor on channel 0
    }

    // Now switch to another device, e.g., on channel 1
    if (tca9548a_select_channel(&mux, 1)) {
        fprintf(stderr, "Failed to select channel 1 on multiplexer\n");
    } else {
        printf("✔ Channel 1 selected — ready to talk to device on channel 1.\n");
        // Here, you would talk to a different sensor/device connected to channel 1
    }

    // === Step 5: Cleanup ===
    // Always clean up hardware interfaces before exiting
    tca9548a_destroy(&mux);    // Free internal resources of multiplexer
    iic_destroy(IIC0);         // Shutdown I2C interface

    return 0;
}
