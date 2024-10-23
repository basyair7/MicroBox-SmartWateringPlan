/*! @file TypeLittleFS
 *  @version 3.0.15
*/

#pragma once

#ifndef TypeLittleFS_h
#define TypeLittleFS_h

#include <Arduino.h>
#include <FS.h>
#include <LittleFS.h>

extern "C" {
	#define LFS LittleFS
	#define LFSAvailable LittleFS.available
	#define LFSisExists LittleFS.exists
	#define openfile LittleFS.open
	#define opendir LittleFS.openDir
	#define removeitem LittleFS.remove
	#define LFS_READ "r"
	#define LFS_WRITE "w"
}

#endif