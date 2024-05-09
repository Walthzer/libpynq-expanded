#include <libpynq.h>
#include <iic.h>
#include "vl53l0x.h"
#include <stdio.h>

 /*
 *  TU/e 5EID0::LIBPYNQ Driver for VL53L0X TOF Sensor
 *  Example Code 
 * 
 *  Original: Larry Bank
 *  Adapted for PYNQ: Walthzer
 * 
 */

extern int vl53l0x_example_single();
extern int vl53l0x_example_dual();

/** This Example program REQUIRES ALL OF:
 * - single.c
 * - dual.c
 * To be present.
**/

int main(void) {
  	pynq_init();

	//Setting up the buttons & LEDs
	//Init the IIC pins
	switchbox_set_pin(IO_AR_SCL, SWB_IIC0_SCL);
	switchbox_set_pin(IO_AR_SDA, SWB_IIC0_SDA);
	iic_init(IIC0);

	/**Test Scripts: Select ONE!
	 * - Single Sensor -> vl53l0x_example_single();
	 * - Dual Sensor -> vl53l0x_example_dual();
	**/	

	/** Connect one sensor to the IIC bus and enjoy! **/
	vl53l0x_example_single();

	/** Connect two sensors to the IIC bus
	 * ONLY CONNECT ONE TO 5V and GND
	 * --If the second sensor is connected to either 5v or GND
	 * --Before the first is initialized, they conflict.
	 * Run the program and follow instructions! **/
	//vl53l0x_example_dual();

	iic_destroy(IIC0);
	pynq_destroy();
	return EXIT_SUCCESS;
}
