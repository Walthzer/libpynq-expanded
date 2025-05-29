// File: TCA9548A.h
/*
 *  TU/e 5EID0::LIBPYNQ Driver for TCA9548A I2C Multiplexer
 *
 *  Written By: Meltedgyro_FPV
 *  Syntax based on libpynq extended by Walthzer
 *
 *  Licensed under GPLv3 or later
 */

#ifndef _TCA9548A_H_
#define _TCA9548A_H_

#include <stdint.h>
#include <libpynq.h>

#define TCA9548A_I2C_ADDR       0x70    /**< Default I²C address */
#define TCA9548A_CHANNEL_COUNT  8       /**< Number of downstream channels */

/**
 * @brief Handle for a TCA9548A multiplexer instance.
 */
typedef struct _tca9548a_mux_ {
    iic_index_t iic_index;    /**< Which I²C bus to talk to the mux on */
    uint8_t     current_channel; /**< Last‐selected channel (0–7), 0xFF if none */
} tca9548a;

/**
 * @brief Initialize the TCA9548A multiplexer.
 *        Disables all channels on startup.
 *
 * @param iic   I²C interface index (IIC0, IIC1, …)
 * @param mux   Pointer to the mux handle (must not be NULL)
 * @return 0 on success, non‐zero on error
 */
extern int tca9548a_init(iic_index_t iic, tca9548a *mux);

/**
 * @brief Tear down the multiplexer, disabling all channels.
 *
 * @param mux   Pointer to a previously inited mux handle
 * @return 0 on success, non‐zero on error
 */
extern int tca9548a_destroy(tca9548a *mux);

/**
 * @brief Select exactly one downstream channel on the mux.
 *
 * @param mux      Pointer to the mux handle
 * @param channel  Which channel to enable (0–7)
 * @return 0 on success, non‐zero if channel ≥8 or on I²C error
 */
extern int tca9548a_select_channel(tca9548a *mux, uint8_t channel);

#endif // _TCA9548A_H_
