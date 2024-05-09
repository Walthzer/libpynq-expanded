 /*
 *  TU/e 5EID0::LIBPYNQ Driver for TCS3472 I2C Colour Sensor
 *
 *  Written By: Walthzer
 * 
 */

//
// Copyright (c) 2024 Walthzer
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

#include <stdint.h>
#include <libpynq.h>

#ifndef _TCSLIB_H_
#define _TCSLIB_H_

#define TCS3472_I2C_ADDR 0x29
#define TCS3472_ID_TCS34725 0x44
#define TCS3472_ID_TCS34727 0x4D

#define TCS3472_INTEG_MIN 1
#define TCS3472_INTEG_MAX 256
#define tcs3472_integration_from_ms(ms) (2.4 * (256 - ATIME))

/**
 * The TCS3472 Family of I2C colour sensors have fixed addresses.
 * Hence why this library uses this address as a magic number.
*/

/**
 * @brief Define the possible gain selections
 */
typedef enum _tcs3472_gain_ {x1, x4, x16, x60} tcs3472_gain;

/**
 * @brief Internal type, do not modify directly. 
 */
typedef struct _tcs3472_sensor_ {
    iic_index_t iic_index;
    uint8_t integration_time; //Longer integration time reduced sensitivity but increases accuracy
    uint8_t wait_time; // Wait time of sensor between taking measuremeants
    uint8_t flags; //{00000 : [2:1]gain : [0]wait_long}
} tcs3472;

/**
 * @struct tcsReading
 * @brief Holds the result of a TCS3472 sensor reading.
 * @param red colour channel
 * @param green colour channel
 * @param bue colour channel
 * @param clear intensity
 * 
 */
typedef struct _tcs3472_reading_ {
    uint16_t red;
    uint16_t green;
    uint16_t blue;
    uint16_t clear;
} tcsReading;

/**
 * @brief Connection test for a TCS3472 Sensor
 * @note USE BEFORE `tofInit`!
 * @param iic IIC Index
 * @return 0 if successful, 1 on error
 */
extern int tcs_ping(iic_index_t iic);

/**
 * @brief Create a configuration for the TCS3472 Sensor.
 * @param sensor Handle to the sensor.
 * @param iic IIC Index
 */
extern void tcs_configure(tcs3472 *sensor, tcs3472_gain gain, );

/**
 * @brief Initialize the TCS3472 Sensor.
 * @param sensor Handle to the sensor.
 * @param iic IIC Index
 * @return 0 if successful, 1 on error
 */
extern int tcs_init(tcs3472 *sensor);

/**
 * @brief Read the current valid data in RGB + Clear.
 * @param sensor Handle to the sensor.
 * @param rgb pointer to store result of reading.
 * @returns 0 if successful, 1 on error
 */
extern int tcs_get_reading(tcs3472 *sensor, tcsReading *rgb);


#endif // _TCSLIB_H_
