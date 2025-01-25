#include <iostream>

#include <application.hpp>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_event.h>

extern "C" void app_main(void)
{
    ESP_ERROR_CHECK(esp_event_loop_create_default());

    application::get_instance().start();

    while(1) {
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}