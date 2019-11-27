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
#include "animations/Felix.h"
#include "animations/AnimationProgram.h"
#include "animations/HeartAnimation.h"
#include "animations/JsonAnimation.h"
#include "animations/Timer.h"

#include <stdio.h>

#include "blewiz/BLECore.h"

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
static Felix felix(display);
static HeartAnimation heart1Animation(display);
static JsonAnimation testJson(display);

Timer animator; // todo parameterize
AnimationProgram animationProgram(animator);

/* static */
BadgeService badgeService(display, animationProgram);

void app_main(void) {
    // fixme check error
    nvs_flash_init();

    ESP_LOGI(TAG, "initializing");

    // fixme check duplicate index error
    animationProgram.putAnimation(0, &meteorShowerAnimation);
    animationProgram.putAnimation(1, &spiralAnimation);
    animationProgram.putAnimation(2, &smearAnimation);
    animationProgram.putAnimation(3, &felix);
    animationProgram.putAnimation(4, &heart1Animation);
    animationProgram.putAnimation(5, &testJson);

    testJson.loadJson();

    badgeService.init();

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

