/*! @file LFSProgram.h
 *  @version 3.0.15
*/

#pragma once

#ifndef LFSProgram_h
#define LFSProgram_h

#include <Arduino.h>
#include <ArduinoJson.h>
#include <vector>
#include "TypeLittleFS.h"

class LFSProgram {
public:
	void setupLFS();
	void reinitializeconfigwifi();
	
public:
	void changeconfigWiFi_STA(const String NEWSSID_STA, const String NEWPASSWORD_STA);
	void changeconfigWiFi_AP(const String NEWSSID_AP, const String NEWPASSWORD_AP);
	
private:
	File file;
	const String configFile = "/CONFIG/config.json";
	const String envBlynk = "/CONFIG/envBlynk.json";

private:
	void initializewifi();
	
private:
	void initializeOrUpdateConfigWiFi(const String& cfile, std::function<void (StaticJsonDocument<500>&)> updateFunc);
	void updateConfigWiFi(const String& cfile, std::function<void (DynamicJsonDocument&)> updateFunc);

private:
	String readconfig(String path);
	bool removefileconfig(String path);
	void writeconfig(String path, String str);
	void listFiles();
	
	std::vector<String> queryDirLFS(const String path) {
		std::vector<String> files;
		Dir dir = opendir(path);
		while (dir.next()) {
			String fileInfo = dir.fileName();
			fileInfo += " - ";
			fileInfo += dir.fileSize();
			files.push_back(fileInfo);
		}
		return files;
	}
	
	void TSprintlnList(const std::vector<String>& files) {
		for (const auto& file : files) {
			Serial.println(file);
		}
	}
	
	void createDirIfNeeded(const String& path) {
		if (!LFSisExists(path)) {
			if (LFS.mkdir(path)) {
				Serial.print(F("Directory"));
				Serial.print(path);
				Serial.println(F(" created"));
			}
			else {
				Serial.print(F("Failed to create "));
				Serial.print(path);
				Serial.println(F(" directory"));
			}
		}
	}
	
};

extern String SSID_STA, PASSWORD_STA;
extern String SSID_AP, PASSWORD_AP;

#endif
