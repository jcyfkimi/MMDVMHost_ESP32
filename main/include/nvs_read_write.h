
#ifndef __NVS_READ_WRITE_H__
#define __NVS_READ_WRITE_H__

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "config.h"

esp_err_t nvs_read_wifi(struct mmdvm_wifi_info *w_info, size_t len);
esp_err_t nvs_write_wifi(struct mmdvm_wifi_info *w_info, size_t len);

#endif