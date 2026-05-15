file(GLOB_RECURSE APP_SOURCES
    "main.cpp"
    "*.cpp"
)

idf_component_register(
    SRCS ${APP_SOURCES}
    INCLUDE_DIRS "."
    REQUIRES
        driver
        esp_wifi
        esp_event
        esp_netif
        nvs_flash
        mqtt
)