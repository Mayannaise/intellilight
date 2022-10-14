/**
 * @file I2C common constants and methods
 */

#define I2C_MASTER_TIMEOUT_MS       1000    /*!< I2C master timeout on read/write commands */
#define I2C_MASTER_NUM              0       /*!< I2C master port number */


/**
 * @brief I2C master initialization
 * @return
 *     - ESP_OK               Success
 *     - ESP_ERR_INVALID_ARG  Error in I2C configuration structure
 *     - ESP_FAIL             Driver installation error
 */
extern esp_err_t i2c_master_init(void);
