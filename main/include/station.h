#ifndef __STATION_H__
#define __STATION_H__

#include "config.h"

#define EXAMPLE_ESP_MAXIMUM_RETRY 5

esp_err_t wifi_init_sta(struct mmdvm_wifi_info *w_info);


#endif