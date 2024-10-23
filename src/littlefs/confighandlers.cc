/*! @file confighandlers.cc
 *  @version 3.0.15
*/

#include "LFSProgram.h"
#include "WIFISETTING.h"
#include "envBlynk.h"

void LFSProgram::updateConfigWiFi(const String& cfile, std::function<void (DynamicJsonDocument&)> updateFunc)
{
	DynamicJsonDocument data(500);
	String readConfig = this->readconfig(cfile), newConfig = "";
	
	if (readConfig == "null") {
		// initialize default values if file does not exist
		data["SSID_STA"] = SSID_STA_DEFAULT;
		data["PASSWORD_STA"] = PASSWORD_STA_DEFAULT;
		data["SSID_AP"] = SSID_AP_DEFAULT;
		data["PASSWORD_AP"] = PASSWORD_AP_DEFAULT;
	}
	else {
		DeserializationError error = deserializeJson(data, readConfig);
		if (error) {
			Serial.print(F("Failed to deserializeJson Update Config WiFi : \n"));
			Serial.println(error.c_str());
			return;
		}
	}
	
	// call the lambda function to update the configuration
	updateFunc(data);
	
	serializeJson(data, newConfig);
	this->writeconfig(cfile, newConfig);
}

void LFSProgram::changeconfigWiFi_STA(const String NEWSSID_STA, const String NEWPASSWORD_STA) {
	this->updateConfigWiFi(this->configFile, [&](DynamicJsonDocument& data) {
		data["SSID_STA"] = NEWSSID_STA;
		data["PASSWORD_STA"] = NEWPASSWORD_STA;
	});
}

void LFSProgram::changeconfigWiFi_AP(const String NEWSSID_AP, const String NEWPASSWORD_AP) {
	this->updateConfigWiFi(this->configFile, [&](DynamicJsonDocument& data) {
		data["SSID_AP"] = NEWSSID_AP;
		data["PASSWORD_AP"] = NEWPASSWORD_AP;
	});
}
