 /*
 *  TU/e 5EID0::LIBPYNQ Driver for TCS3472 Colour Sensor
 *
 *  Written By: Walthzer
 * 
 */

#include <libpynq.h>
#include <tcs3472.h>

#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

int write_byte(iic_index_t iic, uint8_t reg, uint8_t data)
{
  return iic_write_register(iic, TCS3472_I2C_ADDR, reg, &data, 1);
}

int tcs_ping(iic_index_t iic, uint8_t *p_id)
{
  uint8_t temp;
  if(p_id == NULL)
    p_id = &temp;

  int error = iic_read_register(iic, TCS3472_I2C_ADDR, tcs3472_repeat_byte(TCS3472_ID_REG), p_id, 1);
  if(error)
    return TCS3472_ERROR;
  
  return !(*p_id == TCS3472_ID_TCS34725 || *p_id == TCS3472_ID_TCS34727);
}

/**
 * Sets the integration time of the tcs3472. 
 * Longer integration time reduced sensitivity but increases accuracy
 */
int tcs_set_integration(tcs3472 *sensor, uint8_t atime)
{
  sensor->integration_time = atime;
  if(sensor->enabled)
  {
    return write_byte(sensor->iic_index, tcs3472_repeat_byte(TCS3472_ATIME_REG), sensor->integration_time);
  }
  return TCS3472_SUCCES;
}

/**
 * Sets the gain of the tcs3472
 */
int tcs_set_gain(tcs3472 *sensor, tcs3472_gain gain)
{
  sensor->gain = gain;
  if (sensor->enabled == 1)
  {
    return write_byte(sensor->iic_index, tcs3472_repeat_byte(TCS3472_CONTROL_REG), (TCS3472_CONTROL_GAIN & sensor->gain));
  }
  return TCS3472_SUCCES;
}

/**
 * Initialize the TCS3472 Sensor.
 */
int tcs_init(iic_index_t iic, tcs3472 *sensor)
{
  sensor->iic_index = iic;
  //ENABLE
  int error = write_byte(sensor->iic_index, tcs3472_repeat_byte(TCS3472_ENABLE_REG), TCS3472_ENABLE_PON);
  sleep_msec(10); //Allow sensor to recover
  error += write_byte(sensor->iic_index, tcs3472_repeat_byte(TCS3472_ENABLE_REG), TCS3472_ENABLE_PON | TCS3472_ENABLE_AEN);
  //RGBC-INTEGRATION
  error += write_byte(sensor->iic_index, tcs3472_repeat_byte(TCS3472_ATIME_REG), sensor->integration_time > 0 ? sensor->integration_time : tcs3472_integration_from_ms(60));
  //GAIN
  error += write_byte(sensor->iic_index, tcs3472_repeat_byte(TCS3472_CONTROL_REG), (TCS3472_CONTROL_GAIN & sensor->gain));

  sensor->enabled = 1;

  return (error != TCS3472_SUCCES);
}

/**
 * Get ready state of a measurement
 */
int tcs_get_ready(tcs3472 *sensor)
{
  //measurement ready?
  uint8_t state;
  int error = iic_read_register(sensor->iic_index, TCS3472_I2C_ADDR, tcs3472_repeat_byte(TCS3472_STATE_REG), &state, 1); 
  if(error)
    return TCS3472_ERROR;
  return (state & 1);
}

/**
 * Helper to read the 16 bit colour registers
 */
int read_colour_reg(tcs3472 *sensor, uint8_t reg, uint16_t *colour)
{
  uint8_t temp[2];
  int error = iic_read_register(sensor->iic_index, TCS3472_I2C_ADDR, tcs3472_multi_byte(reg), temp, 2);
  *colour = (((uint16_t)temp[1]) << 8) | ((uint16_t)temp[0]);

  return error;
}

/**
 * Read the current valid data in RGB + Clear.
 */
int tcs_get_reading(tcs3472 *sensor, tcsReading *rgb)
{
  int error;

  //Reading colour registers
  error = read_colour_reg(sensor, TCS3472_RED_REG, &rgb->red);
  error += read_colour_reg(sensor, TCS3472_GREEN_REG, &rgb->green);
  error += read_colour_reg(sensor, TCS3472_BLUE_REG, &rgb->blue);
  error += read_colour_reg(sensor, TCS3472_CLEAR_REG, &rgb->clear);

  return (error != TCS3472_SUCCES);
}