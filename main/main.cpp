#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "matrix/matrix.h"

#include "player/Display.h"
#include "animations/SmearAnimation.h"
#include "animations/SpiralAnimation.h"
#include "animations/MeteorShowerAnimation.h"
#include "animations/Felix.h"
#include "player/AnimationProgram.h"
#include "animations/HeartAnimation.h"
#include "animations/JsonAnimation.h"
#include "animations/SpinBottleAnimation.h"
#include "animations/WormholeAnimation.h"
#include "animations/SpinBottle2.h"
#include "animations/EmojiAnimation.h"
#include "animations/Kaleidascope.h"
#include "animations/MarqueeAnimation.h"
#include "animations/DiceAnimation.h"
#include "animations/Party.h"
#include "animations/Weather.h"
#include "animations/MiscellanyAnimation.h"
#include "animations/FunBit64.h"
#include "animations/PaintPixel.h"
#include "animations/Alphabet.h"
#include "animations/Tween.h"
#include "animations/Plasma.h"
#include "animations/Gravity.h"

#include "player/AnimationTask.h"

#include <stdio.h>

#include "blewiz/BLECore.h"

#include "BadgeService.h"
#include "motion/Motion.hpp"

extern "C" {
	void app_main(void);
}

static const char* TAG = "BADGE";

#define REGISTER(index, name, clazz) \
    static clazz name; \
    animationProgram.putAnimation(index, &name);

TaskHandle_t mainTaskHandle;

// initialize the app on a task pinned to the APP core
void mainTask(void *parameters) {
    ESP_LOGI(TAG, "main task running on core: %d", xPortGetCoreID());
    Profiler profiler(true);
    profiler.startTime();

    static Display display( GPIO_NUM_14);

    // the new AnimationTask is a replacement for the old TimerAnimationTask
    // which uses an interruptable semaphore to time the animations
    AnimationTask animator; // todo parameterize
    static AnimationProgram animationProgram(animator);

    /* static */
    BadgeService badgeService(display, animationProgram);

    // fixme check duplicate index error
    REGISTER(0, spiralAnimation, SpiralAnimation);
    REGISTER(1, meteorShowerAnimation, MeteorShowerAnimation);
    REGISTER(2, smearAnimation, SmearAnimation);
    REGISTER(3, felix, Felix);
#if 0 // to conserve memory?
    REGISTER(4, heart1Animation, HeartAnimation);
    REGISTER(5, spinBottle, SpinBottleAnimation);
    REGISTER(6, spinBottle2, SpinBottle2);
    REGISTER(7, wormhole, WormholeAnimation);
    REGISTER(8, testJson, JsonAnimation);
    REGISTER(9, emoji, EmojiAnimation);
    REGISTER(10, kaleidascope, Kaleidascope);
    REGISTER(11, marquee, MarqueeAnimation);
    REGISTER(12, diceAnimation, DiceAnimation);
    REGISTER(13, party, Party)
    REGISTER(14, weather, Weather)
    REGISTER(15, miscellany, MiscellanyAnimation)
    REGISTER(16, funbit, FunBit64)
    REGISTER(17, paintPixel, PaintPixel)
#endif
    REGISTER(18, alphabet, Alphabet);
    REGISTER(19, tween, Tween);
    REGISTER(20, plasma, Plasma)
    REGISTER(21, gravity, Gravity);

    const int defaultIndex = 0;

//    testJson.loadJson();

    // badgeService.setPaintPixel(&paintPixel);
    badgeService.init();

    animator.setCallback(
        [] {
            animationProgram.drawFrame(display);
            display.show();
        }
    );

    display.setBrightness(5);
    animationProgram.setProgram(defaultIndex);
    animator.start();

    profiler.stopTime();

    // start motion
    Motion motion;
    motion.setListeners([](MotionData motionData){
        gravity.setMotion(motionData);
    });
    motion.start();

    // start BLE
    BLECore core;
    core.registerService(&badgeService);
    core.init();

    // main task does nothing but initialize app on core 1
    while(true) {

    }
}

void app_main(void) {
    // fixme check error
    nvs_flash_init();

    ESP_LOGI(TAG, "app_main running on core: %d", xPortGetCoreID());
    ESP_LOGI(TAG, "initializing");

    // run main task on APP core so that RMT interrupts don't collide with BT
    static char name[] = "main task";
    uint16_t stackDepth = 4092;
    UBaseType_t priority = tskIDLE_PRIORITY + 0;
    BaseType_t coreId = 1; // assume that BT runs on core 0
    BaseType_t status = xTaskCreatePinnedToCore(mainTask, name, stackDepth, NULL, priority, &mainTaskHandle, coreId);
    if (status != pdPASS) {
        ESP_LOGE(TAG, "Create task failed: %d", status);
    }

}

