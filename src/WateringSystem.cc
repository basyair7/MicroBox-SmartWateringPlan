/*! @file WateringSystem.cc
 *  @version 1.0.0
*/

#include "WateringSystem.h"
#include "variable.h"

bool WateringSystem::__isRaining__(const int range) {
    int value = analogRead(RAINSENSOR);
    if (value < range) {
        Serial.println(F("Rain detected, no watering plant"));
        return true;
    }

    return false;
}


void WateringSystem::__init__() {
    pinMode(RAINSENSOR, INPUT);
    for (auto i : PINS_GPIO) {
        pinMode(i, OUTPUT);
    }

    digitalWrite(PINS_GPIO[1], OFF);

    this->__MyEEPROM__.get(EEPROM_SAVE_STATE_WATERING, &this->lastWateringDay);

    if (this->lastWateringDay == 0) {
        DateTime now = __myRTC__.DSnow();
        this->lastWateringDay = now.day();
        this->__MyEEPROM__.save_state_watering(this->lastWateringDay);
    }

}

void WateringSystem::__run__(const long __delay__) {
    if ((unsigned long) (millis() - this->LastMillis) >= 1000) {
        this->LastMillis = millis();
        
        DateTime now = __myRTC__.DSnow();
        int currentDay = now.day();

        if (this->isWatering) {
            if ((now.unixtime() - WateringStartTime.unixtime()) >= 7200) {
                this->__stopWatering__();
            }
        }
        else {
            if (currentDay - lastWateringDay >= INTERVALDAYSDEFAULT && !this->__isRaining__(500)) 
            {
                this->__startWatering__(now);
                lastWateringDay = currentDay;
                __MyEEPROM__.save_state_watering(lastWateringDay);
            }
        }
    }
}
