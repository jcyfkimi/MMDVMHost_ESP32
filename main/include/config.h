#ifndef __CONFIG_H__
#define __CONFIG_H__

#define STORAGE_NAMESPACE_WIFI      "wifi_info"
#define WIFI_STORAGE_KEY            "wifi_info"

struct mmdvm_wifi_info
{
    char is_set;
    char ssid[32];
    char pwd[64];
};

#endif