/*! @file DS3231rtc.hh
 *  @version 1.0.1
*/

#pragma once

#ifndef DS3231rtc_hh
#define DS32321rtc_hh

#include <Arduino.h>
#include <SPI.h>
#include <RTClib.h>

class DS3231rtc {
public:
    void begin() {
        while (!this->__rtc__.begin()) {
            Serial.println(F("Status : Couldn't find RTC Module"));
            delay(100);
        }

        if (this->__rtc__.lostPower()) {
            Serial.println(F("Status : RTC Module Lost Power, Setting the time!"));
            this->__rtc__.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }
    }

    DateTime DSnow() {
        return this->__rtc__.now();
    }

    // function to manual adjust RTC time
    void manualAdjust(
        uint8_t month, uint8_t day, uint16_t year,
        uint8_t hour, uint8_t minute, uint8_t second
    ) {
        this->__rtc__.adjust(DateTime(year, month, day, hour, minute, second));
    }

    // function to automatically adjust RTC time
    void autoAdjust(void) {
        this->__rtc__.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }

    // function to get the current date
    template <typename T> 
    void date(T *month, T *day, T *year) {
        this->__now__ = this->DSnow();
        if (month != nullptr) *month = this->__now__.month();
        if (day != nullptr)   *day   = this->__now__.day();
        if (year != nullptr)  *year  = this->__now__.year();
    }

    // function to get the current time
    template <typename T>
    void time(T *hour, T *minute, T *second) {
        this->__now__ = this->DSnow();
        if (hour != nullptr)   *hour   = this->__now__.hour();
        if (minute != nullptr) *minute = this->__now__.minute();
        if (second != nullptr) *second = this->__now__.second();
    }

    // function to get the date as a string
    String datestr(void) {
        return String(this->DSnow().month()) + "/" 
            + String(this->DSnow().day()) + "/"
            + String(this->DSnow().year());
    }

    // function to get the time as a string
    String timestr(void) {
        return String(this->DSnow().hour()) + ":"
            + String(this->DSnow().minute()) + ":"
            + String (this->DSnow().second());
    }

    // function to get day of week
    String getDayOfWeek(void) {
        return this->listDayOfWeek[this->DSnow().dayOfTheWeek()];
    }

private:
    const char listDayOfWeek[7][12] = {
        "Sunday", "Monday", "Tuesday",
        "Wednesday", "Thursday", "Friday",
        "Saturday"
    };

    RTC_DS3231 __rtc__;
    DateTime __now__;
};

#endif
