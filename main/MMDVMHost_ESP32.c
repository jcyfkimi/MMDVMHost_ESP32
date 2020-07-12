/*  WiFi softAP Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#include "soft_ap.h"
#include "config_wifi_sta.h"
#include "nvs_read_write.h"

static const char *TAG = "MMDVMHost_ESP32";

char g_wifi_sta_ssid[32] = {0};
char g_wifi_sta_pwd[64] = {0};

void app_main()
{
    struct mmdvm_wifi_info w_info;
    //Initialize NVS
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    //Read wifi info fram nvs, connect to wifi station if wifi info is set, start ap mode for wifi config if not set.
    memset(&w_info, 0, sizeof(w_info));
    ret = nvs_read_wifi(&w_info, sizeof(w_info));
    if(ret != ESP_OK)
    {
      ESP_LOGE(TAG, "Read wifi info from nvs failed, starting AP mode");
      wifi_init_softap();
      html_config_wifi_sta_init();
    }
    else
    {
      ESP_LOGI(TAG, "Read wifi info from nvs OK, Checking wifi info is set or not");
      if(0x01 == w_info.is_set)
      {
        ESP_LOGI(TAG, "Wifi info is set, start connecting to wifi, ssid = %s, pwd = %s", w_info.ssid, w_info.pwd);
      }
      else
      {
        ESP_LOGI(TAG, "Wifi info is set, start AP mode");
        wifi_init_softap();
        html_config_wifi_sta_init();
      }
      
    }
    ESP_LOGI(TAG, "ESP_WIFI_MODE_AP");

}
