/**
 * @file VEML3328 CRGBIR colour sensor
 */
 
 /* system includes */
#include "driver/i2c.h"

/* local includes */
#include "i2c_common.h"
#include "veml3328.h"


esp_err_t veml3328_configure(void)
{
    esp_err_t err = veml3328_send_command(0x11, 0x80);
    err |= veml3328_send_command(0x10, 0x00);

    return err;
}

uint16_t veml3328_read_channel(const uint8_t channel)
{
    uint8_t rx_data[2];
    const uint8_t tx_data[1] = {channel};

    const esp_err_t err = i2c_master_write_read_device(
        I2C_MASTER_NUM, VEML3328_I2C_SLAVE_ADDR,
        tx_data, sizeof(tx_data), rx_data, sizeof(rx_data),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
    ESP_ERROR_CHECK(err);

    return ((uint16_t)rx_data[1] << 8) | (uint16_t)rx_data[0];
}

esp_err_t veml3328_send_command(const uint8_t data1, const uint8_t data2)
{
    const uint8_t write_buf[3] = {VEML3328_COMMAND_CONFIG, data1, data2};

    return i2c_master_write_to_device(
        I2C_MASTER_NUM, VEML3328_I2C_SLAVE_ADDR,
        write_buf, sizeof(write_buf),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}
