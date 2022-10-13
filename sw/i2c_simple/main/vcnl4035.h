/**
 * @file I2C driver for the VCNL4035 Proximity Sensor (PS) and Ambient Light Sensor (ALS)
 */

/* system includes */
#include "esp_err.h"


#define VCNL4035X01_I2C_SLAVE_ADDR     0x60    /*!< Slave address of the VCNL4035X01 sensor */
#define VCNL40351X01_I2C_SLAVE_ADDR    0x51    /*!< Slave address of the VCNL40351X01 sensor */
#define VCNL40352X01_I2C_SLAVE_ADDR    0x40    /*!< Slave address of the VCNL40352X01 sensor */
#define VCNL40353X01_I2C_SLAVE_ADDR    0x41    /*!< Slave address of the VCNL40353X01 sensor */

#define VCNL4035_COMMAND_ALS_CONF      0x00    /*<! Command code to configure the ALS_CONF1/2 registers */
#define VCNL4035_COMMAND_PS_CONF       0x03    /*<! Command code to configure the PS_CONF1/2 registers */

#define VCNL4035_COMMAND_PS1_DATA      0x08    /*<! Command code to perform a readback of PS1 */
#define VCNL4035_COMMAND_PS2_DATA      0x09    /*<! Command code to perform a readback of PS2 */
#define VCNL4035_COMMAND_PS3_DATA      0x0A    /*<! Command code to perform a readback of PS3 */
#define VCNL4035_COMMAND_ALS_DATA      0x0B    /*<! Command code to perform a readback of ALS */


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
