/*! @file LFSProgram.cc
 *  @version 1.0.0
*/

#include "LFSProgram.h"
#include "WIFISETTING.h"
#include "envBlynk.h"

String SSID_STA = SSID_STA_DEFAULT;
String PASSWORD_STA = PASSWORD_STA_DEFAULT;
String SSID_AP = SSID_AP_DEFAULT;
String PASSWORD_AP = PASSWORD_AP_DEFAULT;

void LFSProgram::listFiles() {
	Serial.println(F("Listing file stored in LittleFS : "));
	Serial.println(F("List Directory / "));
	this->TSprintlnList(this->queryDirLFS("/"));
	Serial.println();
	
	Serial.println(F("List Directory /CONFIG : "));
	this->TSprintlnList(this->queryDirLFS("/CONFIG"));
	Serial.println();
	
	Serial.println(F("List Directory /WEB : "));
	this->TSprintlnList(this->queryDirLFS("/WEB"));
	Serial.println();
	
	Serial.println(F("List Directory /WEB/html : "));
	this->TSprintlnList(this->queryDirLFS("/WEB/html"));
	Serial.println();
	
	Serial.println(F("List Directory /WEB/css : "));
	this->TSprintlnList(this->queryDirLFS("/WEB/css"));
	Serial.println();
	
	Serial.println(F("List Directory /WEB/js : "));
	this->TSprintlnList(this->queryDirLFS("/WEB/js"));
	Serial.println();
}

void LFSProgram::initializeOrUpdateConfigWiFi(const String& cfile, std::function<void (StaticJsonDocument<500>&)> updateFunc)
{
	StaticJsonDocument<500> data;
	String readConfig = this->readconfig(cfile), newConfig = "";
	
	if (readConfig == "null") {
		// initialize default value if file does not exists
		data["SSID_STA"] = SSID_STA_DEFAULT;
		data["PASSWORD_STA"] = PASSWORD_STA_DEFAULT;
		data["SSID_AP"] = SSID_AP_DEFAULT;
		data["PASSWORD_AP"] = PASSWORD_AP_DEFAULT;
	}
	else {
		DeserializationError error = deserializeJson(data, readConfig);
		if (error) {
			Serial.print(F("Failed to deserializeJson initializeOrUpdateConfigWiFi : \n"));
			Serial.println(error.c_str());
			return;
		}
	}
	
	// call the lambda function to update the configuration
	updateFunc(data);
	
	serializeJson(data, newConfig);
	this->writeconfig(cfile, newConfig);
}

void LFSProgram::initializewifi() {
	this->initializeOrUpdateConfigWiFi(this->configFile, [&](StaticJsonDocument<500>& data) {
		SSID_STA = data["SSID_STA"].as<String>();
		PASSWORD_STA = data["PASSWORD_STA"].as<String>();
		SSID_AP = data["SSID_AP"].as<String>();
		PASSWORD_AP = data["PASSWORD_AP"].as<String>();
	});
}

void LFSProgram::reinitializeconfigwifi() {
	this->initializeOrUpdateConfigWiFi(this->configFile, [&](StaticJsonDocument<500>& data) {
		data["SSID_STA"] = SSID_STA_DEFAULT;
		data["PASSWORD_STA"] = PASSWORD_STA_DEFAULT;
		data["SSID_AP"] = SSID_AP_DEFAULT;
		data["PASSWORD_AP"] = PASSWORD_AP_DEFAULT;
	});
}

void LFSProgram::setupLFS() {
	while (!LFS.begin()) {
		Serial.print(F("Failed..."));
		Serial.println(F("Error initializing LittleFS, please try again"));
		Serial.println(F("Done : Error 0x1"));
		delay(150);
	}
	
	this->createDirIfNeeded("/CONFIG");
	this->initializewifi();
	this->listFiles();
	Serial.println(F("\nConfigurate WiFi Client : "));
	Serial.print(F("SSID STA : ")); Serial.println(SSID_STA);
	Serial.print(F("PASSWORD STA : ")); Serial.println(PASSWORD_STA);
	Serial.print(F("SSID AP : ")); Serial.println(SSID_AP);
	Serial.print(F("PASSWORD AP : ")); Serial.println(PASSWORD_AP);
	delay(1000);
	Serial.println(F("Done : No error 0x0\n"));
}
