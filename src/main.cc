/*! @file main.cc
 *  @version 1.0.0
*/

#include "main.h"
#include "LFSProgram.h"
#include "ProgramWiFi.h"
#include "BootButton.h"
#include "WateringSystem.h"
#include "MyEEPROM.hh"
#include "envBlynk.h"
#include <BlynkSimpleEsp8266.h>

ProgramWiFi programWiFi;
BootButton bootbtn = BootButton(BOOTBUTTON, INPUT);
LFSProgram lfssys;
MyEEPROM myeeprom;

void setup() {
	// put your setup here, to run once:
	Serial.begin(9600);
	EEPROM.begin(512);
	WateringSystem::init();
	lfssys.setupLFS();
	bootbtn.begin();

	programWiFi.setup(SSID_STA, PASSWORD_STA, SSID_AP, PASSWORD_AP);
	bool state;
	myeeprom.get(EEPROM_RECOVERY_MODE_ADDR, &state);
	programWiFi.initWiFi(state);
	if (WiFi.getMode() == WIFI_AP) {
		
	}
	else {

	}

}

void loop() {
	// put your main code here, to run repeatedly:
	WateringSystem::run(1000);
}