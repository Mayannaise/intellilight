/**
 * @file Constants and functions for communicating with TP-Link Kasa IoT smart devices
 */

#ifndef INTELLILIGHT_TPLINK_KASA_H
#define INTELLILIGHT_TPLINK_KASA_H


/* system includes */
#include <string.h>
#include <unistd.h>

/* local includes */
#include "wifi.h"


extern const char * tplink_kasa_turn_on;       /*!< Unencrypted JSON string to turn on Kasa smartbulb */
extern const char * tplink_kasa_turn_off;      /*!< Unencrypted JSON string to turn off Kasa smartbulb */

/**
 * @brief XOR Autokey Cipher with starting key of 171
 * @param payload Payload to encrypt
 * @return Encypted payload
 */
void tplink_kasa_encrypt(const char * payload, char * encypted_payload);

/**
 * @brief XOR Autokey Cipher with starting key of 171
 * @param json_string Kasa command in null-terminated JSON string
 * @return Encypted payload
 */
extern bool tplink_kasa_encrypt_and_send(const char * json_string);

#endif
