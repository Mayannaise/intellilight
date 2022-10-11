/**
 * @file PCA9554 I2C GPIO controller (connected to an RGB,W,IR LED)
 */

/* system includes */
#include "esp_err.h"

#define PCA9554_I2C_SLAVE_ADDR          0x27    /*!< Slave address of the PCA9554 I2C GPIO controller */

#define PCA9554_INPUT_PORT_REG          0x00    /*!< Read-only register to get the state of the GPIO inputs */
#define PCA9554_OUTPUT_PORT_REG         0x01    /*!< Write-only register to set the state of the GPIO outputs */
#define PCA9554_POLARITY_INVERSION_REG  0x02    /*!< Read/write register to control the polarity of the input port regisister */
#define PCA9554_CONFIGURATION_REG       0x03    /*!< Control the input/output state of the GPIO pins */

#define PCA9554_IR_LED_GPIO_PIN         0x02    /*!< GPIO pin number to control IR    LED (VSMY1850X01) */
#define PCA9554_RED_LED_GPIO_PIN        0x03    /*!< GPIO pin number to control red   LED (VEML3328)    */
#define PCA9554_GREEN_LED_GPIO_PIN      0x04    /*!< GPIO pin number to control green LED (VEML3328)    */
#define PCA9554_BLUE_LED_GPIO_PIN       0x05    /*!< GPIO pin number to control blue  LED (VEML3328)    */
#define PCA9554_WHITE_LED_GPIO_PIN      0x06    /*!< GPIO pin number to control white LED (VLMW51Q2R3)  */


/**
 * @brief Configure all GPIOs as outputs (to control LED MOSFETs)
 * @return ESP error code
 */
extern esp_err_t pca9554_configure(void);

/**
 * @brief Turn LED on/off
 * @param turn_on true to turn on, false to turn off
 * @param led_pin GPIO pin number of LED to turn on/off
 * @return ESP error code
 */
extern esp_err_t pca9554_enable_led(const uint8_t led_pin, const bool on);
