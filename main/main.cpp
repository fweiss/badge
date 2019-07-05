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
#include "animations/AnimationProgram.h"
#include <stdio.h>

#include "Timer.h"
#include "BTController.h"

#include "BadgeService.h"

extern "C" {
	void app_main(void);
}

#define LED_STRIP_TAG "BADGEP"

#define LED_STRIP_LENGTH 64U
#define LED_STRIP_RMT_INTR_NUM 19U

static Display display( GPIO_NUM_14);

static SpiralAnimation spiralAnimation(display);
static MeteorShowerAnimation meteorShowerAnimation(display);
static SmearAnimation smearAnimation(display);

AnimationProgram animationProgram;

/* static */
BadgeService badgeService(display, animationProgram);

Timer animator;

BTController controller;

void app_main(void)
{
    nvs_flash_init();

    ESP_LOGI(LED_STRIP_TAG, "initializing\n");


    animationProgram.putAnimation(0, &spiralAnimation);
    animationProgram.putAnimation(1, &meteorShowerAnimation);
//    animationProgram.putAnimation(2, smearAnimation);

    controller.init();
    badgeService.init();

    // refactor above
    // BlECore.init
    // appRegister
    // BLECore.setService
    // BLECore does the setup housekeeping with event handler
    // starts the app/server registration (maybe implicitly)
    // delegates other events to service (or services)

    animator.setCallback(
        [] {
            animationProgram.drawFrame();
        }
    );

    display.setBrightness(5);

    animator.start();
}

