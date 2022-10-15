/**
 * @file IntelliLight main application code
 */
 
/* system includes */
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/i2c.h>

/* local includes */
#include "colours.h"
#include "i2c_common.h"
#include "pca9554.h"
#include "tplink_kasa.h"
#include "vcnl4035.h"
#include "veml3328.h"
#include "wifi.h"


/**
 * @brief Flags to remember the current (last commanded) state of the smart bulb
 */
struct smart_bulb_state
{
    bool     on_off;      /*!< Current on/off state of the smartbulb */
    uint8_t  brightness;  /*!< Current brightness (in percent) of the smartbulb */
} current_state;

/**
 * @brief Application main entry point
 */
void app_main(void)
{
    const char *log_tag = "intellilight";
    uint16_t proximity, ambient;
    struct rgb_colour rgb;
    struct hsv_colour hsv;
    char command[200];

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

    /* connect to the configured WiFi network and wait till connected */
    wifi_connect();
    ESP_LOGI(log_tag, "Waiting for IP address");
    while ( !wifi_network_ready() ) {
        vTaskDelay(500 / portTICK_RATE_MS);
    }

    /* turn off smart bulb to begin with */
    tplink_kasa_encrypt_and_send(tplink_kasa_turn_off);
    current_state.on_off = false;

    /* periodically read from the sensors */
    while (true)
    {
        /* wait 500ms */
        vTaskDelay(500 / portTICK_RATE_MS);

        /* read from all the sensors */
        rgb = veml3328_read_colour();
        hsv = colours_rgb_to_hsv(rgb);
        proximity = vcnl4035_read_proximity();
        ambient = vcnl4035_read_ambient_light();
        ESP_LOGD(log_tag, "RGB=%d,%d,%d P=%d A=%d", rgb.r, rgb.g, rgb.b, proximity, ambient);

        /* turn on smartbulb (and green LED) when user is close to the sensor */
        const bool requested_on = proximity > 10;
        if (requested_on != current_state.on_off)
        {
            ESP_LOGI(log_tag, "Turning %s smartbulb", requested_on ? "on" : "off");
            pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, requested_on);
            tplink_kasa_encrypt_and_send(requested_on ? tplink_kasa_turn_on : tplink_kasa_turn_off);
            current_state.on_off = requested_on;
        }

        /* set smart bulb brightness if new brightness is > 5% different from current brightness */
        const uint8_t brightness = fmin((ambient / 30.0), 100.0);
        if ( abs(brightness - current_state.brightness) > 5 )
        {
            ESP_LOGI(log_tag, "Setting smartbulb brightness to %d%%", brightness);   
            snprintf(command, sizeof(command), tplink_kasa_brightness, brightness);
            tplink_kasa_encrypt_and_send(command);
            current_state.brightness = brightness;
        }
    }

    /* shutdown I2C master */
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(log_tag, "I2C unitialised successfully");
}
