/*! @file wifi_sta_config.cc
 *  @version 1.0.0
*/

#include "WebServer.h"
#include "main.h"

void WebServer::WiFiSTAConfig_1(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/config_wifi_sta_1.html", LFS_READ);
    if (!this->file) {
        req->send_P(404, "text/plain", "File not found");
        return;
    }

    // read file content
    size_t fileSize = file.size();
    char *buffer = new char[fileSize + 1];
    file.readBytes(buffer, fileSize);
    buffer[fileSize] = '\0';
    file.close();

    const char *placeholders[] = {
        "%VERSIONPROJECT%",
        "%VERSIONPROJECT%",
        "%SSIDAP%", "%PASSWORDAP%", "%SSIDAP%"
    };

    const char *tags_html[] = {
        __VERSION_PROJECT__.c_str(),
        __VERSION_PROJECT__.c_str(),
        programWiFi.__SSID_AP__.c_str(), programWiFi.__PASSWORD_AP__.c_str(),
        programWiFi.__SSID_AP__.c_str(),
    };

    String page = buffer;
    for (int i = 0; i < (int)(sizeof(tags_html)/sizeof(tags_html[0])); i++) {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send(200, "text/html", page);
    // don't forget to free the memory after use
    delete[] buffer;
}

void WebServer::WiFiSTAConfig_2(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/config_wifi_sta_2.html", LFS_READ);
    if (!this->file) {
        req->send_P(404, "text/plain", "File not found");
        return;
    }

    // read file content
    size_t fileSize = file.size();
    char *buffer = new char[fileSize + 1];
    file.readBytes(buffer, fileSize);
    buffer[fileSize] = '\0';
    file.close();

    // get ip address
    IPAddress clientIP = req->client()->localIP();
    this->LOCALIP = clientIP.toString();

    const char *placeholders[] = {
        "%VERSIONPROJECT%",
        "%VERSIONPROJECT%",
        "%SSIDSTA%", "%PASSWORDSTA%"
        "%LOCALIP%"
    };

    const char *tags_html[] = {
        __VERSION_PROJECT__.c_str(),
        __VERSION_PROJECT__.c_str(),
        programWiFi.__SSID_STA__.c_str(),
        programWiFi.__PASSWORD_STA__.c_str(),
        this->LOCALIP.c_str()
    };

    String page = buffer;
    for (int i = 0; i < (int)(sizeof(tags_html)/sizeof(tags_html[0])); i++) {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send(200, "text/html", page);
    // Don't forget to free the memory after use
    delete[] buffer;
}

void WebServer::SaveWiFiSTAConfig(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/save_config_wifi_sta.html", LFS_READ);
    if (!this->file) {
        req->send_P(404, "text/plain", "File not found");
        return;
    }

    // read file content
    size_t fileSize = file.size();
    char *buffer = new char[fileSize + 1];
    file.readBytes(buffer, fileSize);
    buffer[fileSize] = '\0';
    file.close();

    // get input arguments
    String NEW_SSID_STA, NEW_PASSWORD_STA;
    if (req->hasArg("newssidsta") && req->hasArg("newpasswordsta")) {
        NEW_SSID_STA = req->arg("newssidsta");
        NEW_PASSWORD_STA = req->arg("newpasswordsta");
        lfssys.changeconfigWiFi_STA(NEW_SSID_STA, NEW_PASSWORD_STA);
    }

    // get ip address
    IPAddress clientIP = req->client()->localIP();
    this->LOCALIP = clientIP.toString();

    const char *placeholders[] = {
        "%VERSIONPROJECT%",
        "%NEWSSIDSTA%",
        "%NEWPASSWORDSTA%",
        "%LOCALIP%"
    };

    const char *tags_html[] = {
        __VERSION_PROJECT__.c_str(),
        NEW_SSID_STA.c_str(),
        NEW_PASSWORD_STA.c_str(),
        this->LOCALIP.c_str()
    };

    String page = buffer;
    for (int i = 0; i < (int)(sizeof(tags_html)/sizeof(tags_html[i])); i++) {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send(200, "text/html", page);

    // Don't forget to free the memory after use
    delete[] buffer;
}
