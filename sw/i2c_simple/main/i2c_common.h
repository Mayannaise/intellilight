/**
 * @file I2C common constants and methods
 */
 
#define I2C_MASTER_SCL_IO           CONFIG_I2C_MASTER_SCL      /*!< GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           CONFIG_I2C_MASTER_SDA      /*!< GPIO number used for I2C master data  */
#define I2C_MASTER_FREQ_HZ          400000                     /*!< I2C master clock frequency = 400kHz */
#define I2C_MASTER_TX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                          /*!< I2C master doesn't need buffer */

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
