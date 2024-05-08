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

int vl53l0x_example_dual(void) {
	int i;
	//Setup Sensor A
	printf("Initialising Sensor A:\n");

	//Change the Address of the VL53L0X
	uint8_t addrA = 0x69;
	i = tofSetAddress(IIC0, 0x29, addrA);
	printf("---Address Change: ");
	if(i != 0)
	{
		printf("Fail\n");
		return 1;
	}
	printf("Succes\n");
	
	i = tofPing(IIC0, addrA);
	printf("---Sensor Ping: ");
	if(i != 0)
	{
		printf("Fail\n");
		return 1;
	}
	printf("Succes\n");

	//Create a sensor struct
	vl53x sensorA;

	//Initialize the sensor

	i = tofInit(&sensorA, IIC0, addrA, 0);
	if (i != 0)
	{
		printf("---Init: Fail\n");
		return 1;
	}

	uint8_t model, revision;

	tofGetModel(&sensorA, &model, &revision);
	printf("---Model ID - %d\n", model);
	printf("---Revision ID - %d\n", revision);
	printf("---Init: Succes\n");
	fflush(NULL);

	printf("\n\nNow Power Sensor B!!\nPress \"Enter\" to continue...\n");
	getchar();

	//Setup Sensor B
	printf("Initialising Sensor B:\n");

	//Use the base addr of 0x29 for sensor B
	//It no longer conflicts with sensor A.
	uint8_t addrB = 0x29;	
	i = tofPing(IIC0, addrB);
	printf("---Sensor Ping: ");
	if(i != 0)
	{
		printf("Fail\n");
		return 1;
	}
	printf("Succes\n");

	//Create a sensor struct
	vl53x sensorB;

	//Initialize the sensor

	i = tofInit(&sensorB, IIC0, addrB, 0);
	if (i != 0)
	{
		printf("---Init: Fail\n");
		return 1;
	}

	tofGetModel(&sensorB, &model, &revision);
	printf("---Model ID - %d\n", model);
	printf("---Revision ID - %d\n", revision);
	printf("---Init: Succes\n");
	fflush(NULL); //Get some output even if the distance readings hang
	printf("\n");

	uint32_t iDistance;
	for (i=0; i<1200; i++)
	{
		iDistance = tofReadDistance(&sensorA);
		printf("A => %dmm -- ", iDistance);
		iDistance = tofReadDistance(&sensorB);
		printf("B => %dmm\n", iDistance);
		sleep_msec(100);
	}

	iic_destroy(IIC0);
	pynq_destroy();
	return EXIT_SUCCESS;
}
