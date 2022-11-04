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
    uint8_t brightness;     /*!< Current brightness (in percent) of the smartbulb */
    struct hsv_colour hsv;  /*!< Current colour (in HSV) of the smartbulb */
} current_state;

/**
 * @brief Parameters used to scale raw sensor readings to useful data
 */
struct sensor_scale
{
    const uint16_t min_raw;       /*!< Raw minimum value */
    const uint16_t max_raw;       /*!< Raw maximum value */
    const uint8_t  min_scaled;    /*!< Scaled minimum value */
    const uint8_t  max_scaled;    /*!< Scaled maximum value */
};

/**
 * @brief Scale raw sensor readings
 * @param reading Raw sensor value to scale
 * @param scale Sensor scaling data
 * @return Scaled value
 */
uint8_t scale_sensor_reading(const uint16_t reading, const struct sensor_scale scale)
{
    const uint16_t clipped_value = fmin(fmax(reading, scale.min_raw), scale.max_raw);
    const uint16_t range_raw = scale.max_raw - scale.min_raw;
    const uint16_t range_scaled = scale.max_scaled - scale.min_scaled;
    const float factor = ((clipped_value - scale.min_raw) / (float)range_raw);
    return (uint8_t)round((range_scaled * factor) + scale.min_scaled);
}

/**
 * @brief Application main entry point
 */
void app_main(void)
{
    const char *log_tag = "intellilight";
    uint16_t proximity, ambient;
    struct rgb_colour rgb;
    struct hsv_colour hsv;
    const struct sensor_scale als_scale = {10, 70, 20, 100};
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

    /* wait till network is ready */
    pca9554_enable_led(PCA9554_BLUE_LED_GPIO_PIN, true);
    ESP_LOGI(log_tag, "Waiting for connection to smartbulb");
    while ( !wifi_network_ready() ) {
        vTaskDelay(500 / portTICK_RATE_MS);
    }

    /* turn off smart bulb to begin with */
    snprintf(command, sizeof(command), tplink_kasa_on_off, 0);
    tplink_kasa_encrypt_and_send(command);
    current_state.on_off = false;

    /* periodically read from the sensors */
    while (true)
    {
        /* turn off green LED when reading the colour sensor to avoid feedback */
        pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, true);
        vTaskDelay(500 / portTICK_RATE_MS);
        pca9554_enable_led(PCA9554_GREEN_LED_GPIO_PIN, false);
        vTaskDelay(500 / portTICK_RATE_MS);

        /* read from all the sensors */
        rgb = veml3328_read_colour();
        hsv = colours_rgb_to_hsv(rgb);
        proximity = vcnl4035_read_proximity();
        ambient = vcnl4035_read_ambient_light();
        ESP_LOGI(log_tag, "RGB=%d,%d,%d P=%d A=%d", rgb.r, rgb.g, rgb.b, proximity, ambient);

        /* turn on smartbulb based on the proximity sensor value */
        /* i.e. when user is close to the sensor */
        const bool requested_on = (proximity > 5);
        if (requested_on != current_state.on_off)
        {
            ESP_LOGI(log_tag, "Turning %s smartbulb", requested_on ? "on" : "off");
            snprintf(command, sizeof(command), tplink_kasa_on_off, requested_on);
            tplink_kasa_encrypt_and_send(command);
            current_state.on_off = requested_on;
        }
        /* if the bulb is off dont bother trying to change the color and brightness*/
        if (!current_state.on_off)
        {
            continue;
        }

        /* set smart bulb brightness based on ambient light level */
        /* only update if new brightness is > 10% different from current brightness */
        const uint8_t brightness = scale_sensor_reading(ambient, als_scale);
        if ( abs(brightness - current_state.brightness) > 10 )
        {
            ESP_LOGI(log_tag, "Setting smartbulb brightness to %d%%", brightness);   
            snprintf(command, sizeof(command), tplink_kasa_brightness, brightness);
            tplink_kasa_encrypt_and_send(command);
            current_state.brightness = brightness;
        }

        /* set smart bulb colour (hue/saturation) based on measured room light colour */
        /* only update if new hue is > 10 degrees different from current hue */
        if ( abs(current_state.hsv.h - hsv.h) > 10 )
        {
            ESP_LOGI(log_tag, "Setting smartbulb hue to %.0f degrees", hsv.h);   
            snprintf(command, sizeof(command), tplink_kasa_hsv, (int)round(hsv.h), 50);
            tplink_kasa_encrypt_and_send(command);
            current_state.hsv = hsv;
        }
    }

    /* shutdown I2C master */
    ESP_ERROR_CHECK(i2c_driver_delete(I2C_MASTER_NUM));
    ESP_LOGI(log_tag, "I2C unitialised successfully");
}
