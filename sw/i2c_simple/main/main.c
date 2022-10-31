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
    bool on_off;            /*!< Current on/off state of the smartbulb */
    int hyst_counter;       /*!< Hyteresis counter to prevent toggling on/off too much */
    uint8_t brightness;     /*!< Current brightness (in percent) of the smartbulb */
    struct hsv_colour hsv;  /*!< Current colour (in HSV) of the smartbulb */
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
    const float max_brightness = 100.0;
    const float min_brightness = 20.0;
    const float scale_brightness = 1.2;
    char command[200];

    /* setup I2C bus as master */
    ESP_LOGI(log_tag, "Configuring ESP as I2C master");
    ESP_ERROR_CHECK(i2c_master_init());

    /* configure I2C slave devices */
    ESP_LOGI(log_tag, "Configuring sensor boards");
    ESP_ERROR_CHECK(vcnl4035_configure());  /* PS and ALS */
    ESP_ERROR_CHECK(pca9554_configure());   /* RGB LED and arrow LEDs */
    ESP_ERROR_CHECK(veml3328_configure());  /* colour sensor */

    /* connect to the configured WiFi network */
    pca9554_enable_led(PCA9554_RED_LED_GPIO_PIN, true);
    wifi_connect();
    vTaskDelay(1000 / portTICK_RATE_MS);

    /* wait till netowrk is ready */
    pca9554_enable_led(PCA9554_BLUE_LED_GPIO_PIN, true);
    ESP_LOGI(log_tag, "Waiting for IP address");
    while ( !wifi_network_ready() ) {
        vTaskDelay(500 / portTICK_RATE_MS);
    }

    /* turn off smart bulb to begin with */
    snprintf(command, sizeof(command), tplink_kasa_on_off, 0);
    tplink_kasa_encrypt_and_send(command);
    current_state.on_off = false;

    /* everything ready, turn on the green LED */
    pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, true);

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
        ESP_LOGI(log_tag, "RGB=%d,%d,%d P=%d A=%d", rgb.r, rgb.g, rgb.b, proximity, ambient);

        /* turn on smartbulb based on the proximity sensor value */
        /* i.e. when user is close to the sensor */
        const bool requested_on = (proximity > 4);
        if (requested_on != current_state.on_off)
        {
            if (current_state.hyst_counter++ > 2)
            {
                ESP_LOGI(log_tag, "Turning %s smartbulb", requested_on ? "on" : "off");
                snprintf(command, sizeof(command), tplink_kasa_on_off, requested_on);
                tplink_kasa_encrypt_and_send(command);
                current_state.on_off = requested_on;
                current_state.hyst_counter = 0;
            }
        }
        else
        {
            current_state.hyst_counter = 0;
        }

        /* if the bulb is off dont bother trying to change the color and brightness*/
        if (!current_state.on_off)
        {
            continue;
        }

        /* set smart bulb brightness based on ambient light level */
        /* only update if new brightness is > 10% different from current brightness */
        const uint8_t brightness = fmax(fmin((ambient / scale_brightness), max_brightness), min_brightness);
        if ( abs(brightness - current_state.brightness) > 10 )
        {
            ESP_LOGI(log_tag, "Setting smartbulb brightness to %d%%", brightness);   
            snprintf(command, sizeof(command), tplink_kasa_brightness, brightness);
            tplink_kasa_encrypt_and_send(command);
            current_state.brightness = brightness;
        }

        /* set smart bulb colour (hue/saturation) based on measured room light colour */
        /* only update if new hue is > 5 degrees different from current hue */
        if ( abs(current_state.hsv.h - hsv.h) > 5 )
        {
            ESP_LOGI(log_tag, "Setting smartbulb hue to %.0f degrees", hsv.h);   
            snprintf(command, sizeof(command), tplink_kasa_hsv, hsv.h, 100);
            tplink_kasa_encrypt_and_send(command);
            current_state.hsv = hsv;
        }
    }

    /* shutdown I2C master */
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(log_tag, "I2C unitialised successfully");
}
