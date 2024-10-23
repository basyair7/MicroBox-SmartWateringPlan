/*! @file tools.cc
 *  @version 3.0.15
*/

#include "LFSProgram.h"

String LFSProgram::readconfig(String path) {
	String val = "";
	this->file = openfile(path, LFS_READ);
	if (this->file) {
		while (this->file.available()) {
			char c = this->file.read();
			val += c;
		}
		this->file.close();
	}
	else {
		Serial.println(F("Failed to open file to writing"));
		val = "null";
	}
	
	return val;
}

void LFSProgram::writeconfig(String path, String str) {
	if (LFSisExists(path)) {
		removeitem(path);
	}
	
	this->file = openfile(path, LFS_WRITE);
	if (this->file) {
		this->file.write((const uint8_t *)str.c_str(), str.length());
		this->file.close();
	}
	else {
		Serial.println(F("Failed to create a new file config.json"));
		return;
	}
}

bool LFSProgram::removefileconfig(String path) {
	if (!LFSisExists(path)) {
		return false;
	}
	
	return removeitem(path);
}