/*  ----------------------------------------------------------------------------
    File: main.c
    Author(s):  Lucas Bruder <LBruder@me.com>
    Date Created: 11/23/2016
    Last modified: 11/26/2016

    ------------------------------------------------------------------------- */

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "led_strip/led_strip.h"
#include "animations/display.h"
#include "animations/SmearAnimation.h"
#include "animations/SpiralAnimation.h"
#include "animations/MeteorShowerAnimation.h"
#include <stdio.h>

#include "Timer.h"

extern "C" {
	void app_main(void);
}

#define LED_STRIP_TAG "LED STRIP"

#define LED_STRIP_LENGTH 64U
#define LED_STRIP_RMT_INTR_NUM 19U

//Display display(&ledStrip);
Display display( GPIO_NUM_14);
static SpiralAnimation animation(display);

#include "soc/timer_group_struct.h"
#include "driver/timer.h"

#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
//#define TIMER_INTERVAL0_SEC   (3.4179) // sample test interval for the first timer
#define TIMER_INTERVAL0_SEC   (0.030) // sample test interval for the first timer
#define TIMER_INTERVAL1_SEC   (5.78)   // sample test interval for the second timer
#define TEST_WITHOUT_RELOAD   0        // testing will be done without auto reload
#define TEST_WITH_RELOAD      1        // testing will be done with auto reload

//static void drawFrame() {
//	static uint8_t r = 0;
//	r = (r + 3) % 256;
//}



void main_led_task(void *args) {


//	TickType_t lastTick = xTaskGetTickCount();
//	const TickType_t period = 10;
//
	while (1) {
//		drawFrame();
		vTaskDelay(50 / portTICK_PERIOD_MS);
	}
}

Timer animator;

void app_main(void)
{
    nvs_flash_init();

    ESP_LOGI(LED_STRIP_TAG, "initializing\n");

//    example_tg0_timer_init(TIMER_0, TEST_WITHOUT_RELOAD, TIMER_INTERVAL0_SEC);

    animator.setCallback(
        []() {
            animation.drawFrame();
        }
    );

//    Timer::timerIsr((void*) 0);

    animator.start();


//	TaskHandle_t main_task_handle;
//    BaseType_t task_created = xTaskCreate(main_led_task,
//                                            "main_led_task",
//                                            ESP_TASK_MAIN_STACK,
//                                            NULL,
//                                            ESP_TASK_MAIN_PRIO,
//                                            &main_task_handle);
//
//    (void)task_created;
//    vTaskDelete(NULL);

}

