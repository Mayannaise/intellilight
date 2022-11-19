/**
 * @file I2C driver for the VCNL4035 Proximity Sensor (PS) and Ambient Light Sensor (ALS)
 */

#ifndef INTELLILIGHT_VCNL4035_H
#define INTELLILIGHT_VCNL4035_H

/* system includes */
#include "esp_err.h"

#define VCNL4035X01_I2C_SLAVE_ADDR     0x60    /*!< Slave address of the VCNL4035X01 sensor */
#define VCNL40351X01_I2C_SLAVE_ADDR    0x51    /*!< Slave address of the VCNL40351X01 sensor */
#define VCNL40352X01_I2C_SLAVE_ADDR    0x40    /*!< Slave address of the VCNL40352X01 sensor */
#define VCNL40353X01_I2C_SLAVE_ADDR    0x41    /*!< Slave address of the VCNL40353X01 sensor */

#define VCNL4035_COMMAND_ALS_CONF      0x00    /*<! Command code to configure the ALS_CONF1/2 registers */
#define VCNL4035_COMMAND_ALS_THDL      0x01    /*<! Command code to configure the ALS low threshold register */
#define VCNL4035_COMMAND_ALS_THDH      0x02    /*<! Command code to configure the ALS high threshold register */
#define VCNL4035_COMMAND_PS_CONF       0x03    /*<! Command code to configure the PS_CONF1/2 registers */
#define VCNL4035_COMMAND_PS_THDL       0x06    /*<! Command code to configure the PS low threshold register */
#define VCNL4035_COMMAND_PS_THDH       0x07    /*<! Command code to configure the PS high threshold register */
#define VCNL4035_COMMAND_PS1_DATA      0x08    /*<! Command code to perform a readback of PS1 */
#define VCNL4035_COMMAND_PS2_DATA      0x09    /*<! Command code to perform a readback of PS2 */
#define VCNL4035_COMMAND_PS3_DATA      0x0A    /*<! Command code to perform a readback of PS3 */
#define VCNL4035_COMMAND_ALS_DATA      0x0B    /*<! Command code to perform a readback of ALS */
#define VCNL4035_COMMAND_INT_FLAG      0x0D    /*<! Command code to perform a readback of INT flag */
#define VCNL4035_COMMAND_DEVICE_ID     0x0E    /*<! Command code to read device ID */

#define vcnl4035_proximity_threshold   100     /*<! Distance over which the smartbulb should be turned on */

/**
 * @brief Configure the VCNL4035 proximity and ambient light sensor
 * @return ESP error code
 */
extern esp_err_t vcnl4035_configure(void);

/**
 * @brief Get a reading from the ambient light sensor
 * @return Raw reading from sensor
 */
extern uint16_t vcnl4035_read_ambient_light(void);

/**
 * @brief Get a reading from the proximity sensor
 * @return Raw reading from sensor
 */
extern uint16_t vcnl4035_read_proximity(void);

/**
 * @brief Read the proximity INT flag
 * @return INT flag value
 */
extern uint8_t vcnl4035_read_int_flag(void);

/**
 * @brief Read the device ID
 * @return Device ID
 */
extern uint16_t vcnl4035_read_device_id(void);

#endif
