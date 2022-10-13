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
#include "pca9554.h"
#include "vcnl4035.h"
#include "veml3328.h"


/**
 * @brief Application main entry point
 */
void app_main(void)
{
    const char *log_tag = "intellilight";
    uint16_t red_value, green_value, blue_value, proximity;

    /* setup I2C bus as master */
    ESP_LOGI(log_tag, "Configuring ESP as I2C master");
    ESP_ERROR_CHECK(i2c_master_init());

    /* configure I2C slave devices */
    ESP_LOGI(log_tag, "Configuring sensor boards");
    ESP_ERROR_CHECK(vcnl4035_configure());  /* PS and ALS */
    ESP_ERROR_CHECK(pca9554_configure());   /* RGB LED and arrow LEDs */
    ESP_ERROR_CHECK(veml3328_configure());  /* colour sensor */

    /* blink the red LED (also "down arrow" gesture) */
    pca9554_enable_led(PCA9554_RED_LED_GPIO_PIN, true);
    vTaskDelay(500 / portTICK_RATE_MS);
    pca9554_enable_led(PCA9554_RED_LED_GPIO_PIN, false);

    /* blink the green LED (also "close enough" gesture) */
    pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, true);
    vTaskDelay(500 / portTICK_RATE_MS);
    pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, false);

    /* blink the blue LED (also "enter" gesture) */
    pca9554_enable_led(PCA9554_BLUE_LED_GPIO_PIN, true);
    vTaskDelay(500 / portTICK_RATE_MS);
    pca9554_enable_led(PCA9554_BLUE_LED_GPIO_PIN, false);

    /* periodically read from the sensors every second */
    while (true)
    {
        vTaskDelay(1000 / portTICK_RATE_MS);
        red_value   = veml3328_read_channel(VEML3328_COMMAND_R_DATA);
        green_value = veml3328_read_channel(VEML3328_COMMAND_G_DATA);
        blue_value  = veml3328_read_channel(VEML3328_COMMAND_B_DATA);
        proximity   = vcnl4035_read_proximity();
        ESP_LOGI(log_tag, "RGB=%d,%d,%d P=%d", red_value, green_value, blue_value, proximity);
    }

    /* shutdown I2C master */
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(log_tag, "I2C unitialised successfully");
}
