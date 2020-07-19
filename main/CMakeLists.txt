idf_component_register(SRCS "MMDVMHost_ESP32.c"
                            "wireless/soft_ap.c"
                            "wireless/station.c"
                            "http/config_mmdvm_dmr.c"
                            "http/config_wifi_sta.c"
                            "nvs_rw/nvs_read_write.c"
                    INCLUDE_DIRS "./include")
