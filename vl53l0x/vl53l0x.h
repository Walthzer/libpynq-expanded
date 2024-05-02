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

//
// Read the model and revision of the
// tof sensor
//
extern int tofGetModel(uint8_t *model, uint8_t *revision);

//
// Read the current distance in mm
//
extern uint32_t  tofReadDistance(void);

//
// Opens a file system handle to the I2C device
// sets the device continous capture mode
// allows selection between the default mode (30-800mm) and the long range mode (30-2000mm).
// default: bLongRange = 0;
extern int tofInit(iic_index_t iic, uint8_t addr, int bLongRange);

#endif // _TOFLIB_H
