/*! @file info.h
 *  @version 1.0.0
*/

#pragma once

#ifndef info_h
#define info_h

#include <Arduino.h>

#define NAMEPROJECT		"MicroBOX (Smart Watering Plant)"
#define CODENAME		"MicroBox"

#define VERSIONPROJECT	"1.0.0"
#define HWVERSION		"1.0.0"
#define SWVERSION		"1.0.0"
#define BUILDDATE		"10/13/2024"
#define REGION			"INDONESIA"

class Info {
protected:
	const String __NAME_PROJECT__ = NAMEPROJECT;
	const String __CODE_NAME__ = CODENAME;
	const String __VERSION_PROJECT__ = VERSIONPROJECT;
	const String __HW_VERSION__ = HWVERSION;
	const String __SW_VERSION__ = SWVERSION;
	const String __BUILD_DATE__ = BUILDDATE;
	const String __REGION__ = REGION;
};

#endif
