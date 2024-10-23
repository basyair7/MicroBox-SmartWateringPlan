/*! @file wifi_ap_config.cc
 *  @version 1.0.0
*/

#include "WebServer.h"
#include "main.h"

void WebServer::WiFiAPConfig_1(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/config_wifi_ap_1.html", LFS_READ);
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
        "%VERSIONPROJECT%", "%VERSIONPROJECT%", "%SSIDAP%",
        "%PASSWORDAP%", "%SSIDAP%"
    };
    const char *tags_html[] = {
        __VERSION_PROJECT__.c_str(), __VERSION_PROJECT__.c_str(),
        programWiFi.__SSID_AP__.c_str(), programWiFi.__PASSWORD_AP__.c_str(), programWiFi.__SSID_AP__.c_str()
    };

    String page = buffer;
    for (int i = 0; i < (int)(sizeof(tags_html)/sizeof(tags_html[0])); i++) {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send(200, "text/html", page);
    // don't forget to free the memory after use
    delete[] buffer;
}

void WebServer::WiFiAPConfig_2(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/config_wifi_ap_2.html", LFS_READ);
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
        "%VERSIONPROJECT%", "%VERSIONPROJECT%", 
        "%SSIDAP%", "%PASSWORDAP%", "%LOCALIP%"
    };

    const char *tags_html[] = {
        __VERSION_PROJECT__.c_str(), __VERSION_PROJECT__.c_str(),
        programWiFi.__SSID_AP__.c_str(), programWiFi.__PASSWORD_AP__.c_str(),
        this->LOCALIP.c_str()
    };

    String page = buffer;
    for (int i = 0; i < (int) (sizeof(tags_html)/sizeof(tags_html[0])); i++) {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send(200, "text/html", page);
    // don't forget to free the memory after use
    delete[] buffer;
}

void WebServer::SaveWiFiAPConfig(AsyncWebServerRequest *req) {
    this->file = openfile("/WEB/html/save_config_wifi_ap.html", LFS_READ);
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
    String NEW_SSID_AP, NEW_PASSWORD_AP;
    if (req->hasArg("newssidap") && req->hasArg("newpasswordap")) {
        NEW_SSID_AP = req->arg("newssidap");
        NEW_PASSWORD_AP = req->arg("newpasswordap");
        lfssys.changeconfigWiFi_AP(NEW_SSID_AP, NEW_PASSWORD_AP);
    }

    // get ip address
    IPAddress clientIP = req->client()->localIP();
    this->LOCALIP = clientIP.toString();

    const char *placeholders[] = {
        "%VERSIONPROJECT%" "%NEWSSIDAP%", "%NEWPASSWORDAP%", "%LOCALIP%"
    };

    const char *tags_html[] = {
        __VERSION_PROJECT__.c_str(),
        NEW_SSID_AP.c_str(), NEW_PASSWORD_AP.c_str(),
        this->LOCALIP.c_str()
    };

    String page = buffer;
    for (int i = 0; i < (int)(sizeof(tags_html)/sizeof(tags_html[i])); i++) {
        page.replace(placeholders[i], tags_html[i]);
    }

    req->send(200, "text/html", page);
    // don't forget to free the memory after use
    delete[] buffer;
}
