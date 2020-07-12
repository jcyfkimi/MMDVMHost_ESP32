#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "nvs_read_write.h"
#include "config.h"

static const char *TAG = "NVS_FLASH_RW";

esp_err_t nvs_read_wifi(struct mmdvm_wifi_info *w_info, size_t len)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;
    size_t required_size = 0;

    ESP_LOGI(TAG, "NVS_READ: Read wifi info");

    err = nvs_open(STORAGE_NAMESPACE_WIFI, NVS_READWRITE, &nvs_handle);
    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "NVS_READ: Open NVS error");
        return err;
    }
    else
    {
        ESP_LOGI(TAG, "NVS_READ: Open NVS OK");
    }

    // For read, we need get the length first and then read out the data
    err = nvs_get_blob(nvs_handle, WIFI_STORAGE_KEY, NULL, &required_size);
    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "NVS_READ: Get length failed");
        return err;
    }
    else
    {
        ESP_LOGI(TAG, "NVS_READ: Get length OK, length = %d", required_size);
    }

    err = nvs_get_blob(nvs_handle, WIFI_STORAGE_KEY, w_info, &required_size);
    if(err == ESP_ERR_NVS_NOT_FOUND)
    {
        ESP_LOGE(TAG, "NVS_READ: Key doesn't exist");
        return err;
    }
    else if (err == ESP_ERR_NVS_INVALID_HANDLE)
    {
        ESP_LOGE(TAG, "NVS_READ: handle has been closed or is NULL");
        return err;
    }
    else if (err == ESP_ERR_NVS_INVALID_NAME)
    {
        ESP_LOGE(TAG, "NVS_READ: name doesn’t satisfy constraints");
        return err; 
    }
    else if (err == ESP_ERR_NVS_INVALID_LENGTH)
    {
        ESP_LOGE(TAG, "NVS_READ: length is not sufficient to store data");
        return err; 
    }
    else
    {
        ESP_LOGI(TAG, "NVS_READ: Get data OK, is_set = %d, ssid = %s, pwd = %s", w_info->is_set, w_info->ssid, w_info->pwd);
    }

    nvs_close(nvs_handle);
    
    return ESP_OK;
}
esp_err_t nvs_write_wifi(struct mmdvm_wifi_info *w_info, size_t len)
{
    nvs_handle_t nvs_handle;
    esp_err_t err;

    ESP_LOGI(TAG, "NVS_WRITE: Save wifi info");

    err = nvs_open(STORAGE_NAMESPACE_WIFI, NVS_READWRITE, &nvs_handle);
    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "NVS_WRITE: Open NVS error");
        return err;
    }
    else
    {
        ESP_LOGI(TAG, "NVS_WRITE: Open NVS OK");
    }

    err = nvs_set_blob(nvs_handle, WIFI_STORAGE_KEY, w_info, len);
    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "NVS_WRITE: set nvs blob failed");
        return err;
    }
    else
    {
        ESP_LOGI(TAG, "NVS_WRITE: set nvs blob OK");
    }

    err = nvs_commit(nvs_handle);
    if(err != ESP_OK)
    {
        ESP_LOGE(TAG, "NVS_WRITE: nvs commit failed");
        return err;
    }
    else
    {
        ESP_LOGI(TAG, "NVS_WRITE: nvs commit OK");
    }

    nvs_close(nvs_handle);

    return ESP_OK;
}
