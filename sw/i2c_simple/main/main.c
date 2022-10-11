/**
 * @file IntelliLight main application code
 */
 
/* system includes */
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/i2c.h>

/* local includes */
#include "i2c_common.h"
#include "veml3328.h"
#include "pca9554.h"

static const char *TAG = "intellilight";

/**
 * @brief I2C master initialization
 * @return
 *     - ESP_OK               Success
 *     - ESP_ERR_INVALID_ARG  Error in I2C configuration structure
 *     - ESP_FAIL             Driver installation error
 */
static esp_err_t i2c_master_init(void)
{
    const int i2c_master_port = I2C_MASTER_NUM;

    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(i2c_master_port, &conf);

    return i2c_driver_install(i2c_master_port, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
}

/**
 * @brief Application main entry point
 */
void app_main(void)
{
    uint16_t red_value, green_value, blue_value;

    /* setup I2C bus as master */
    ESP_ERROR_CHECK(i2c_master_init());
    ESP_LOGI(TAG, "I2C initialised successfully");

    /* blink the LEDs */
    ESP_LOGI(TAG, "Configuring RGB LED over I2C");
    ESP_ERROR_CHECK(pca9554_configure());

    ESP_ERROR_CHECK(pca9554_enable_led(PCA9554_RED_LED_GPIO_PIN, true));
    vTaskDelay(500 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(pca9554_enable_led(PCA9554_RED_LED_GPIO_PIN, false));

    ESP_ERROR_CHECK(pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, true));
    vTaskDelay(500 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, false));

    ESP_ERROR_CHECK(pca9554_enable_led(PCA9554_BLUE_LED_GPIO_PIN, true));
    vTaskDelay(500 / portTICK_RATE_MS);
    ESP_ERROR_CHECK(pca9554_enable_led(PCA9554_BLUE_LED_GPIO_PIN, false));

    /* setup colour sensor */
    ESP_LOGI(TAG, "Configuring colour sensor over I2C");
    ESP_ERROR_CHECK(veml3328_send_command(0x11, 0x80));
    ESP_ERROR_CHECK(veml3328_send_command(0x10, 0x00));

    /* periodically read from colour sensor every second */
    while (true)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
        red_value   = veml3328_read_channel(VEML3328_COMMAND_R_DATA);
        green_value = veml3328_read_channel(VEML3328_COMMAND_G_DATA);
        blue_value  = veml3328_read_channel(VEML3328_COMMAND_B_DATA);
        ESP_LOGI(TAG, "RGB = %d,%d,%d", red_value, green_value, blue_value);
    }

    /* shutdown I2C master */
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(TAG, "I2C unitialised successfully");
}
