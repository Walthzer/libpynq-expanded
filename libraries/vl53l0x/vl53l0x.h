#include <stdbool.h>
#include <stdint.h>
#include <libpynq.h>

#ifndef _TOFLIB_H_
#define _TOFLIB_H_


 /*
 *  TU/e 5EID0::LIBPYNQ Driver for VL53L0X TOF Sensor
 *
 *  Original C library: Larry Bank
 *  Adapted for PYNQ: Walthzer
 * 
 */

//
// Copyright (c) 2017 Larry Bank
// email: bitbank@pobox.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

/**
 * @brief Internal type, do not modify directly. 
 */
typedef struct _vl53_sensor_ {
    iic_index_t iic_index;
    uint8_t baseAddr;
    uint8_t stop_variable;
    uint32_t measurement_timing_budget_us;
} vl53x;

/**
 * @brief Set IIC address of a VL53L0X Sensor
 * @param addr IIC Address of the sensor
 * @param iic IIC Index
 * @param newAddr IIC Target Address of the sensor
 * @return 0 if successful, 1 on error
 */
extern int tofSetAddress(iic_index_t iic, uint8_t addr, uint8_t newAddr);

/**
 * @brief Connection test for a VL53L0X Sensor
 * @note USE BEFORE `tofInit`!
 * @param addr IIC Address of the sensor
 * @param iic IIC Index
 * @return 0 if successful, 1 on error
 */
extern int tofPing(iic_index_t iic, uint8_t addr);

/**
 * @brief Initialize the VL53L0X Sensor
 * @param sensor Handle to the sensor.
 * @param iic IIC Index
 * @param addr IIC Address of the sensor
 * @param bLongRange 0 => default mode (30-800mm) or 1 => long range mode (30-2000mm)
 * @return 0 if successful, 1 on error
 */
extern int tofInit(vl53x *sensor, iic_index_t iic, uint8_t addr, int bLongRange);

/**
 * @brief Read the model and revision of the VL53L0X Sensor
 * @param sensor Handle to the sensor.
 * @param model pointer to store model
 * @param revision pointer to store revision
 * @return 0 if successful, 1 on error
 */
extern int tofGetModel(vl53x *sensor, uint8_t *model, uint8_t *revision);

/**
 * @brief Read current distance in mm
 * @param sensor Handle to the sensor.
 * @returns distance in mm
 */
extern uint32_t tofReadDistance(vl53x *sensor);


#endif // _TOFLIB_H
