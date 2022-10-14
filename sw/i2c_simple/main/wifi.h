/**
 * @file WiFi functionality
 */

#include <string.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"


/**
 * @brief Connect to a WiFi network using the configured SSID and password
 */
extern void wifi_connect(void);

/**
 * @brief Encrypt and send JSON string
 * @param payload Encrypted data to send
 * @param length Length of payload
 * @return true if TCP transfer was successful, false otherwise
 */
extern bool wifi_tcp_transfer(const char *payload, const int length);
