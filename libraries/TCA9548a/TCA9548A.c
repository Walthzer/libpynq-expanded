// File: TCA9548A.c
/*
 *  TU/e 5EID0::LIBPYNQ Driver for TCA9548A I2C Multiplexer
 *
 *  Written By: Meltedgyro_FPV
 *  Syntax based on libpynq extended by Walthzer
 */

#include "TCA9548A.h"
#include <libpynq.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * @brief Low-level write of the 8-bit control register (selects channels).
 */
static int write_control(iic_index_t iic, uint8_t control)
{
    /* The TCA9548A has its control register at pointer 0x00 */
    return iic_write_register(iic, TCA9548A_I2C_ADDR, 0x00, &control, 1);
}

int tca9548a_init(iic_index_t iic, tca9548a *mux)
{
    if (!mux) return 1;
    mux->iic_index = iic;
    mux->current_channel = 0xFF;  /* no channel selected */
    /* Disable all downstream channels */
    return write_control(iic, 0x00);
}

int tca9548a_destroy(tca9548a *mux)
{
    if (!mux) return 1;
    mux->current_channel = 0xFF;
    /* Again disable everything */
    return write_control(mux->iic_index, 0x00);
}

int tca9548a_select_channel(tca9548a *mux, uint8_t channel)
{
    if (!mux || channel >= TCA9548A_CHANNEL_COUNT)
        return 1;
    uint8_t control = (1u << channel);
    int err = write_control(mux->iic_index, control);
    if (!err) {
        mux->current_channel = channel;
    }
    return err;
}
