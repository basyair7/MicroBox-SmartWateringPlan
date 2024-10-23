/*! @file ProgramWiFi.h
 *  @version 1.0.0
*/

#pragma once

#ifndef ProgramWiFi_h
#define ProgramWiFi_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <functional>

class ProgramWiFi {
public:
	String __SSID_STA__, __PASSWORD_STA__;
	String __SSID_AP__, __PASSWORD_AP__;
	String LOCALIPServer;

public:
	void setup(const String __SSID_STA__, const String __PASSWORD_STA__, const String __SSID_AP__, const String __PASSWORD_AP__);
	void initWiFi(bool state);
	void optimizeWiFi(WiFiSleepType_t type, bool persistentWiFi) {
		WiFi.setSleepMode(type);
		WiFi.persistent(persistentWiFi);
	}
	
private:
	WiFiEventHandler wifiConnectHandler, wifiDisconnectHandler;
	void onWiFiConnect(const WiFiEventStationModeGotIP& event);
	void onWiFiDisconnect(const WiFiEventStationModeDisconnected& event);
	void Mode_AP(), Mode_STA();
};

#endif
