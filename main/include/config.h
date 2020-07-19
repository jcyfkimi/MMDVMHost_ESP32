#ifndef __CONFIG_H__
#define __CONFIG_H__

#define STORAGE_NAMESPACE_WIFI              "wifi_info"
#define WIFI_STORAGE_KEY                    "wifi_info"

#define STORAGE_NAMESPACE_MMDVM_GENERAL     "General"
#define GENERAL_STORAGE_KEY                 "General"

#define STORAGE_NAMESPACE_DMR               "DMR"
#define DMR_STORAGE_KEY                     "DMR"

#define STORAGE_NAMESPACE_DMR_NET           "DMR_NET"
#define DMR_NET_STORAGE_KEY                 "DMR_NET"

enum DMR_BEACONS
{
    DMR_BEACONS_OFF,
    DMR_BEACONS_NETWORK,
    DMR_BEACONS_TIMED
};

struct mmdvm_wifi_info
{
    char is_set;
    char ssid[32];
    char pwd[64];
};

struct mmdvm_general_info
{
    char is_set;
    char callsign[16];
    unsigned int dmr_id;
    unsigned int tx_freq;
    unsigned int rx_freq;
    unsigned int rf_power;
    float latitude;
    float longtitude;
    int height;
    char location[32];
    char description[64];
    char url[32];
};

struct mmdvm_dmr_info
{
    char is_set;
    char enable;
    enum DMR_BEACONS dmr_beacon;
    unsigned int dmr_beacon_interval;
    unsigned int dmr_beacon_duration;
    unsigned int dmr_id;                        //This dmr_id could be mmdvm_general_info + 01, 02, 03....in order to identify different active hostopts.
    unsigned int colorcode;
};

struct mmdvm_dmr_net_info
{
    char is_set;
    char enable;
    char address[64];
    unsigned int port;
    unsigned int jitter;
    char password[32];
    char slot1;
    char slot2;
};

#endif