/**
 * @file I2C driver for the VCNL4035 Proximity Sensor and Ambient Light Sensor
 */
 
 /* system includes */
#include "driver/i2c.h"

/* local includes */
#include "i2c_common.h"
#include "vcnl4035.h"


static esp_err_t vcnl4035_configure_als(void)
{
    const uint8_t ALS_CONF1 = 0x00;
    const uint8_t ALS_CONF2 = 0x01;
    const uint8_t write_buf[3] = {VCNL4035_COMMAND_ALS_CONF, ALS_CONF1, ALS_CONF2};

    return i2c_master_write_to_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        write_buf, sizeof(write_buf),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);
}

static esp_err_t vcnl4035_configure_ps(void)
{
    const uint8_t PS_CONF1 = 0x0E; /* integration time = 8T (max), PS=enabled */
    const uint8_t PS_CONF2 = 0x01; /* enable the proximity "trigger close" interrupt */
    const uint8_t PS_CONF3 = 0x12; /* enable smart persistence, enable logic output */
    const uint8_t PS_MS    = 0x07; /* 200mA IR LED current*/

    const uint8_t write_buf1[3] = { VCNL4035_COMMAND_PS_CONF,     PS_CONF1, PS_CONF2 };
    const uint8_t write_buf2[3] = { VCNL4035_COMMAND_PS_CONF + 1, PS_CONF3, PS_MS    };
    const uint8_t write_buf3[3] = { VCNL4035_COMMAND_PS_THDH,     100,      0        };
    
    const esp_err_t err1 = i2c_master_write_to_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        write_buf1, sizeof(write_buf1),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    const esp_err_t err2 = i2c_master_write_to_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        write_buf2, sizeof(write_buf2),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    const esp_err_t err3 = i2c_master_write_to_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        write_buf3, sizeof(write_buf3),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    return err1 | err2 | err3;
}

esp_err_t vcnl4035_configure(void)
{
    const esp_err_t ps_err = vcnl4035_configure_ps();
    const esp_err_t als_err = vcnl4035_configure_als();

    return als_err | ps_err;
}

uint16_t vcnl4035_read_ambient_light(void)
{
    uint8_t rx_data[2];
    const uint8_t tx_data[1] = {VCNL4035_COMMAND_ALS_DATA};

    const esp_err_t err = i2c_master_write_read_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        tx_data, sizeof(tx_data), rx_data, sizeof(rx_data),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    ESP_ERROR_CHECK(err);

    return ((uint16_t)rx_data[1] << 8) | (uint16_t)rx_data[0];
}

uint16_t vcnl4035_read_proximity(void)
{
    uint8_t rx_data[2];
    const uint8_t tx_data[1] = {VCNL4035_COMMAND_PS1_DATA};

    const esp_err_t err = i2c_master_write_read_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        tx_data, sizeof(tx_data), rx_data, sizeof(rx_data),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    ESP_ERROR_CHECK(err);

    return ((uint16_t)rx_data[1] << 8) | (uint16_t)rx_data[0];
}

uint8_t vcnl4035_read_int_flag(void)
{
    uint8_t rx_data[2];
    const uint8_t tx_data[1] = { VCNL4035_COMMAND_INT_FLAG };

    const esp_err_t err = i2c_master_write_read_device(
        I2C_MASTER_NUM, VCNL4035X01_I2C_SLAVE_ADDR,
        tx_data, sizeof(tx_data), rx_data, sizeof(rx_data),
        I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);

    ESP_ERROR_CHECK(err);

    return rx_data[1];
}
