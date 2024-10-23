/*! @file variable.h
 *  @version 1.0.0
*/

#pragma once

#ifndef variable_h
#define variable_h

#include <Arduino.h>

#define BOOTBUTTON	D3
#define RAINSENSOR	A0

inline const uint16_t PINS_GPIO[2] = {D4, D5};
inline const uint8_t LEDINDIKATOR = PINS_GPIO[0];

#define INTERVALDAYSDEFAULT 2

// don't replace it.. EEPROM wifi state
#define EEPROM_RECOVERY_MODE_ADDR  0x4
#define EEPROM_SAVE_STATE_WATERING 0x8

#endif
