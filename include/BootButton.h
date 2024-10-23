/*! @file BootButton.h
 *  @version 1.0.0
*/

#pragma once

#ifndef BootButton_h
#define BootButton_h

#include <Arduino.h>
#include <pushbutton.h>
#include "MyEEPROM.hh"

class BootButton {
public:
	BootButton(uint8_t pin, uint8_t mode) : __BootBtn__(pin, mode) {
		/*TODO(Not yet implemented)*/
	}
	
	void begin() {
		this->__BootBtn__.init();
		this->__wifiState__ = this->__MyEEPROM__.read(EEPROM_RECOVERY_MODE_ADDR);
	}
	
	void WiFiMode() {
		this->__currentButtonState__ = this->__BootBtn__.digitalReadPushButton();
		if (this->__currentButtonState__ != this->__lastButtonState__)
			this->__buttonChange__ = true;
		
		if (this->__buttonChange__) {
			if (this->__currentButtonState__ == false) {
				this->__wifiState__ = !this->__wifiState__;
				this->__MyEEPROM__.save_state_recovery(this->__wifiState__);
				delay(5);
				
				Serial.println(F("Mode Recovery : "));
				Serial.println(this->__wifiState__ ? F("ENABLE") : F("DISABLE"));
				delay(2000);
				ESP.reset();
			}
			this->__buttonChange__ = false;
		}
		this->__lastButtonState__ = this->__currentButtonState__;
	}
	
private:
	MyEEPROM __MyEEPROM__;
	PushButtonDigital __BootBtn__;
	bool __currentButtonState__ = false;
	bool __lastButtonState__ = false;
	bool __buttonChange__ = false;
	bool __wifiState__ = false;
};

#endif
