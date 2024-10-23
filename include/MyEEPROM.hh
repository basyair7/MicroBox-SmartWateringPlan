/*! @file EEPROM.hh
 *  @version 1.0.0
*/

#pragma once

#ifndef MyEEPROM_hh
#define MyEEPROM_hh

#include <Arduino.h>
#include <EEPROM.h>
#include "variable.h"

class MyEEPROM {
public:
    template <typename T>
    void get(const int address, T *val) const {
        EEPROM.get(address, *val);
    }
    
    uint8_t read(const int address) const {
        return EEPROM.read(address);
    }

    template <typename T>
    bool save_state_recovery(T &state) const {
        EEPROM.put(EEPROM_RECOVERY_MODE_ADDR, state);
    #if defined(ESP8266) || defined(ESP32)
        return EEPROM.commit();
    #else
        return true;
    #endif
    }

    template <typename T>
    bool save_state_watering(T &state) const {
        EEPROM.put(EEPROM_SAVE_STATE_WATERING, state);
    #if defined(ESP8266) || defined(ESP32)
        return EEPROM.commit();
    #else
        return true;
    #endif
    }
};

#endif
