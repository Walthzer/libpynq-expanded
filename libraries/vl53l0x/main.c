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

int main(void) {
  pynq_init();

  // Setting up the buttons & LEDs
  //Init the IIC pins
  switchbox_set_pin(IO_AR_SCL, SWB_IIC0_SCL);
  switchbox_set_pin(IO_AR_SDA, SWB_IIC0_SDA);
  iic_init(IIC0);

	int i;
	uint32_t iDistance;
	uint8_t model, revision;

	// For other boards (e.g. OrangePi) it's 0
	i = tofInit(IIC0, 0x29, 0); // set long range mode (up to 2m)
	if (i != 1)
	{
		return -1; // problem - quit
	}
	printf("VL53L0X device successfully opened.\n");
	tofGetModel(&model, &revision);
	printf("Model ID - %d\n", model);
	printf("Revision ID - %d\n", revision);
	fflush(NULL); //Get some output even is distance readings hang
	for (i=0; i<1200; i++) // read values 20 times a second for 1 minute
	{
		iDistance = tofReadDistance();
		printf("Distance = %dmm\n", iDistance);
		sleep_msec(100); // 50ms
	}

  iic_destroy(IIC0);
  pynq_destroy();
  return EXIT_SUCCESS;
}
