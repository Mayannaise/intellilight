/**
 * @file I2C common constants and methods
 */
   
/* system includes */
#include <driver/i2c.h>

/* local includes */
#include "i2c_common.h"


#define I2C_MASTER_FREQ_HZ          400000    /*!< I2C master clock frequency = 400kHz */
#define I2C_MASTER_TX_BUF_DISABLE   0         /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0         /*!< I2C master doesn't need buffer */

/**
 * @brief I2C master initialization
 * @return
 *     - ESP_OK               Success
 *     - ESP_ERR_INVALID_ARG  Error in I2C configuration structure
 *     - ESP_FAIL             Driver installation error
 */
esp_err_t i2c_master_init(void)
{
    const int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = CONFIG_I2C_MASTER_SDA,
        .scl_io_num = CONFIG_I2C_MASTER_SCL,
        .sda_pullup_en = GPIO_PULLUP_DISABLE,
        .scl_pullup_en = GPIO_PULLUP_DISABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}
