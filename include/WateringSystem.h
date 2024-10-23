/*! @file WateringSystem.h
 *  @version 1.0.0
*/

#pragma once

#ifndef WATERINGSYSTEM_H
#define WATERINGSYSTEM_H

#include <Arduino.h>
#include "DS3231rtc.hh"
#include "MyEEPROM.hh"

#define ON  LOW
#define OFF HIGH

class WateringSystem {
public:
    static WateringSystem &instance() {
        static WateringSystem instance;
        return instance;
    }

    static void init() { instance().__init__();}
    static void run(long __delay__) { instance().__run__(__delay__); }

private:
    void __init__();
    void __run__(const long __delay__);
    bool __isRaining__(const int range);

    void __startWatering__(DateTime now) {
        Serial.println(F("Watering Started..."));
        digitalWrite(PINS_GPIO[1], ON);
        WateringStartTime = now;
        isWatering = true;
    }

    void __stopWatering__() {
        Serial.println(F("Watering Plant Done..."));
        digitalWrite(PINS_GPIO[1], OFF);
        isWatering = false;
    }

private:
    DateTime WateringStartTime;
    int lastWateringDay;
    bool isWatering = false;
    
    unsigned long LastMillis = 0;

private:
    DS3231rtc __myRTC__;
    MyEEPROM __MyEEPROM__;
};

#endif
