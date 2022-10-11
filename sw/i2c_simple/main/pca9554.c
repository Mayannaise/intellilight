/**
 * @file PCA9554 I2C GPIO controller (connected to an RGBWIR LED)
 */

/* system includes */
#include <stdio.h>
#include <driver/i2c.h>

/* local includes */
#include "i2c_common.h"
#include "pca9554.h"

esp_err_t pca9554_configure(void)
{
    const uint8_t write_buf[2] = {PCA9554_CONFIGURATION_REG, 0x00};

    return i2c_master_write_to_device(
        I2C_MASTER_NUM, PCA9554_I2C_SLAVE_ADDR,
        write_buf, sizeof(write_buf),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

esp_err_t pca9554_enable_led(const uint8_t led_pin, const bool on)
{
    const uint8_t write_buf[2] = {PCA9554_OUTPUT_PORT_REG, (uint8_t)(on << led_pin)};

    return i2c_master_write_to_device(
        I2C_MASTER_NUM, PCA9554_I2C_SLAVE_ADDR,
        write_buf, sizeof(write_buf),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}
