/**
 * @file VEML3328 CRGBIR colour sensor
 */
 
#ifndef INTELLILIGHT_VEML3328_H
#define INTELLILIGHT_VEML3328_H


/* system includes */
#include "esp_err.h"

/* local includes */
#include "colours.h"


#define VEML3328_I2C_SLAVE_ADDR     0x10    /*!< Slave address of the VEML3328 sensor */
#define VEML3328_COMMAND_CONFIG     0x00    /*!< Command to configure VEML3328 sensor */
#define VEML3328_COMMAND_C_DATA     0x04    /*!< Command to read VEML3328 sensor clear value */
#define VEML3328_COMMAND_R_DATA     0x05    /*!< Command to read VEML3328 sensor red value */
#define VEML3328_COMMAND_G_DATA     0x06    /*!< Command to read VEML3328 sensor green value */
#define VEML3328_COMMAND_B_DATA     0x07    /*!< Command to read VEML3328 sensor blue value */
#define VEML3328_COMMAND_IR_DATA    0x08    /*!< Command to read VEML3328 sensor infrared value */


/**
 * @brief Configure the colour sensor
 * @return ESP error code
 */
extern esp_err_t veml3328_configure(void);

/**
 * @brief Read from one of the colour sensor channels (C,R,G,B,IR)
 * @param channel Channel register from which to read
 * @return Colour value read from sensor
 */
extern uint16_t veml3328_read_channel(const uint8_t channel);

/**
 * @brief Read RGB value from sensor
 * @return Colour value in rgb
 */
extern struct rgb_colour veml3328_read_colour(void);

/**
 * @brief Write two-byte command code to VEML3328 colour sensor
 * @param data1 First command byte to send
 * @param data2 Second command byte to send
 * @return ESP error code
 */
extern esp_err_t veml3328_send_command(const uint8_t data1, const uint8_t data2);

#endif
