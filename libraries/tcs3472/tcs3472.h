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
#define TCS3472_I2C_CMD 0x80

#define TCS3472_ID_REG 0x12
#define TCS3472_STATE_REG 0x13
#define TCS3472_ENABLE_REG 0x00
#define TCS3472_ATIME_REG 0x01
#define TCS3472_WTIME_REG 0x03 
#define TCS3472_CONTROL_REG 0x0F //single -> gain

//Data
#define TCS3472_CLEAR_REG 0x14
#define TCS3472_RED_REG 0x16
#define TCS3472_GREEN_REG 0x18
#define TCS3472_BLUE_REG 0x1A

#define TCS3472_ID_TCS34725 0x44
#define TCS3472_ID_TCS34727 0x4D
#define TCS3472_INTEG_MIN 1
#define TCS3472_INTEG_MAX 256

#define TCS3472_ENABLE_PON 0x01 //Clock
#define TCS3472_ENABLE_AEN 0x02 //ADC
#define TCS3472_CONTROL_GAIN 0x03

#define TCS3472_SUCCES 0
#define TCS3472_ERROR 1
#define TCS3472_READY 2

#define tcs3472_repeat_byte(reg) reg | 0x80
#define tcs3472_multi_byte(reg) reg | 0xA0
#define tcs3472_integration_from_ms(ms) 256 - (ms / 2.4)
#define CLAMP_255(a) (((a)>(255))?(255):(a))

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
    int enabled;
    iic_index_t iic_index;
    uint8_t integration_time; //Longer integration time lowers sensitivity but increases accuracy
    tcs3472_gain gain;
} tcs3472;
#define TCS3472_EMPTY {0, IIC0, 0, x1}

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
 * @param iic IIC Index
 * @param p_id pointer to push ID -> set to NULL
 * @return 0 if successful, 1 on error
 */
extern int tcs_ping(iic_index_t iic, uint8_t *p_id);

/**
 * @brief Sets the integration time of the tcs3472. 
 * Longer integration time lowers sensitivity but increases accuracy
 * @param sensor Handle to the sensor.
 * @param atime Integration time in 2.4ms increments. 0xFF::2.4ms 0x00::700ms
 * @return 0 if successful, 1 on error
 * @note Will update the setting on the actual sensor if its initialised.
 * @note else the setting is stored for `tcs_init`
 */
extern int tcs_set_integration(tcs3472 *sensor, uint8_t atime);

/**
 * @brief Sets the gain of the tcs3472
 * @param sensor Handle to the sensor.
 * @param gain one of tcs3472_gain: `{x1 x4 x16 x60}`
 * @return 0 if successful, 1 on error
 * @note Will update the setting on the actual sensor if its initialised.
 * @note else the setting is stored for `tcs_init`
 */
extern int tcs_set_gain(tcs3472 *sensor, tcs3472_gain gain);

/**
 * @brief Initialize the TCS3472 Sensor.
 * @param sensor Handle to the sensor.
 * @param iic IIC Index
 * @return 0 if successful, 1 on error
 */
extern int tcs_init(iic_index_t iic, tcs3472 *sensor);

/**
 * @brief Get ready state of a measurement.
 * @param sensor Handle to the sensor.
 * @returns 0 if waiting, 1 on ready, 2 on error
 */
extern int tcs_get_ready(tcs3472 *sensor);

/**
 * @brief Read the current valid data in RGB + Clear.
 * @param sensor Handle to the sensor.
 * @param rgb pointer to store result of reading.
 * @returns 0 if successful, 1 on error
 */
extern int tcs_get_reading(tcs3472 *sensor, tcsReading *rgb);


#endif // _TCSLIB_H_
