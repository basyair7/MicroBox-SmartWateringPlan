/*! @file ProgramWiFi.cc
 *  @version 1.0.0
*/

#include "ProgramWiFi.h"
#include "BootButton.h"
#include "variable.h"

void ProgramWiFi::setup(const String __SSID_STA__, const String __PASSWORD_STA__, const String __SSID_AP__, const String __PASSWORD_AP__)
{
	this->__SSID_STA__ = __SSID_STA__;
	this->__PASSWORD_STA__ = __PASSWORD_STA__;
	this->__SSID_AP__ = __SSID_AP__;
	this->__PASSWORD_AP__ = __PASSWORD_AP__;
}

// run program if WiFi connecting
void ProgramWiFi::onWiFiConnect(const WiFiEventStationModeGotIP& event)
{
	Serial.print(F(""));
	Serial.print(F("Connected to : ")); Serial.println(this->__SSID_STA__);
	Serial.print(F("IP Address : ")); Serial.println(event.ip);
	this->LOCALIPServer = event.ip.toString().c_str();
}

void ProgramWiFi::onWiFiDisconnect(const WiFiEventStationModeDisconnected& event)
{
	WiFi.disconnect();
	WiFi.begin(this->__SSID_STA__, this->__PASSWORD_STA__);
}

// run program mode STA
void ProgramWiFi::Mode_STA() {
	BootButton bootbutton(BOOTBUTTON, INPUT);
	// setup WiFi mode AP STA
	// WiFi.mode(WIFI_AP_STA);
	WiFi.mode(WIFI_STA);
	
	// register event handlers
	using namespace std;
	this->wifiConnectHandler = WiFi.onStationModeGotIP(bind(&ProgramWiFi::onWiFiConnect, this, placeholders::_1));
	this->wifiDisconnectHandler = WiFi.onStationModeDisconnected(bind(&ProgramWiFi::onWiFiDisconnect, this, placeholders::_1));
	
	// initializing WiFi and connecting to an SSID
	WiFi.begin(this->__SSID_STA__.c_str(), this->__PASSWORD_STA__.c_str());
	Serial.print(F("Connecting to WiFi..."));
	while (WiFi.status() != WL_CONNECTED) {
		bootbutton.WiFiMode();
		Serial.print(F("."));
		delay(500);
	}
	
	// RSSI
	Serial.print(F("\nRSSI : "));
	Serial.println(WiFi.RSSI());
}

// run program mode AP
void ProgramWiFi::Mode_AP() {
	// setup wifi mode AP
	WiFi.mode(WIFI_AP);
	
	// initializing Access Point
	WiFi.softAP(this->__SSID_AP__.c_str(), this->__PASSWORD_AP__.c_str());
	
	// get IP Address
	this->LOCALIPServer = WiFi.softAPIP().toString().c_str();
	Serial.print(F("IP Address : "));
	Serial.println(this->LOCALIPServer);
	Serial.println();
}

/* program initialize wifi
 * Mode STA = true
 * Mode AP = false
*/

void ProgramWiFi::initWiFi(bool state) {
	Serial.print(F("\nMode WiFi : "));
	Serial.println(state ? F("WIFI_STA") : F("WIFI_AP"));
	if (state) {
		this->Mode_STA();
	}
	else {
		this->Mode_AP();
	}
}
