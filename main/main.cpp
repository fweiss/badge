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
#include "BLECore.h"

#include "BadgeService.h"

extern "C" {
	void app_main(void);
}

static const char* TAG = "BADGE";

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

void app_main(void) {
    // fixme check error
    nvs_flash_init();

    ESP_LOGI(TAG, "initializing");

    animationProgram.putAnimation(0, &spiralAnimation);
    animationProgram.putAnimation(1, &meteorShowerAnimation);
//    animationProgram.putAnimation(2, smearAnimation);

    badgeService.init();

    // refactor above
    // BlECore.init
    // appRegister
    // BLECore.setService
    // BLECore does the setup housekeeping with event handler
    // starts the app/server registration (maybe implicitly)
    // delegates other events to service (or services)
    BLECore core;
    core.registerService(&badgeService);
    core.init();

    animator.setCallback(
        [] {
            animationProgram.drawFrame();
        }
    );

    display.setBrightness(5);

    animator.start();
}

