/*! @file WebServer.h
 *  @version 1.0.0
*/

#pragma once

#ifndef WebServer_h
#define WebServer_h

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <ESPAsyncWebServer.h>
#include <ESPAsyncTCP.h>
#include <ElegantOTA.h>
#include <vector>
#include "TypeLittleFS.h"
#include "ProgramWiFi.h"
#include "info.h"

class WebServer : protected Info {
public:
	WebServer(int port) : serverAsync(port) { /*TODO(Not yet implemented)*/}
	void ServerInit();
	void updateOTAloop();
	
private:
	void DHTCheck(AsyncWebServerRequest *req);
	void RainCheck(AsyncWebServerRequest *req);
	void index(AsyncWebServerRequest *req);
	void GetSwitchStatus(AsyncWebServerRequest *req);
	void EnableBlynk(AsyncWebServerRequest *req);

// config wifi
private:
	void WiFiAPConfigMain(AsyncWebServerRequest *req);
	void WiFiAPConfig_1(AsyncWebServerRequest *req);
	void WiFiAPConfig_2(AsyncWebServerRequest *req);
	void SaveWiFiAPConfig(AsyncWebServerRequest *req);
	void WiFiSTAConfigMain(AsyncWebServerRequest *req);
	void WiFiSTAConfig_1(AsyncWebServerRequest *req);
	void WiFiSTAConfig_2(AsyncWebServerRequest *req);
	void SaveWiFiSTAConfig(AsyncWebServerRequest  *req);
	
private:
	void Reboot(AsyncWebServerRequest *req);
	void handleNotFound(AsyncWebServerRequest *req);
	void RecoveryPage(AsyncWebServerRequest *req);
	void Reset_System(AsyncWebServerRequest *req);
	
// global config
private:
	File file;
	String LOCALIP;
	AsyncWebServer serverAsync;
	
};

#endif
