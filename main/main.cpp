#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_system.h"
#include "esp_task.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

#include "led_strip/led_strip.h"
#include "matrix/matrix.h"

#include "animations/display.h"
#include "animations/SmearAnimation.h"
#include "animations/SpiralAnimation.h"
#include "animations/MeteorShowerAnimation.h"
#include "animations/Felix.h"
#include "animations/AnimationProgram.h"
#include "animations/HeartAnimation.h"
#include "animations/JsonAnimation.h"
#include "animations/SpinBottleAnimation.h"
#include "animations/WormholeAnimation.h"
#include "animations/SpinBottle2.h"
#include "animations/Timer.h"
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

#include "animations/AnimationTask.h"

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

#define PLUG(clazz, name, index) \
    static clazz name(display); \
    animationProgram.putAnimation(index, &name);


static SpiralAnimation spiralAnimation(display);
static MeteorShowerAnimation meteorShowerAnimation(display);
static SmearAnimation smearAnimation(display);
static Felix felix(display);
static HeartAnimation heart1Animation(display);
static JsonAnimation testJson(display);
static SpinBottleAnimation spinBottle(display);
static WormholeAnimation wormhole(display);
static SpinBottle2 spinBottle2(display);
static EmojiAnimation emoji(display);
static Kaleidascope kaleidascope(display);
static MarqueeAnimation marquee(display);
static DiceAnimation diceAnimation(display);

AnimationTask animator; // todo parameterize
AnimationProgram animationProgram(animator);

/* static */
BadgeService badgeService(display, animationProgram);

void app_main(void) {
    // fixme check error
    nvs_flash_init();

    ESP_LOGI(TAG, "initializing");

    // fixme check duplicate index error
    animationProgram.putAnimation(0, &spiralAnimation);
    animationProgram.putAnimation(1, &meteorShowerAnimation);
    animationProgram.putAnimation(2, &smearAnimation);
    animationProgram.putAnimation(3, &felix);
    animationProgram.putAnimation(4, &heart1Animation);
    animationProgram.putAnimation(5, &spinBottle);
    animationProgram.putAnimation(6, &spinBottle2);
    animationProgram.putAnimation(7, &wormhole);
    animationProgram.putAnimation(8, &testJson);
    animationProgram.putAnimation(9, &emoji);
    animationProgram.putAnimation(10, &kaleidascope);
    animationProgram.putAnimation(11, &marquee);
    animationProgram.putAnimation(12, &diceAnimation);
    PLUG(Party, party, 13)
    PLUG(Weather, weather, 14)
    PLUG(MiscellanyAnimation, miscellany, 15)
    PLUG(FunBit64, funbit, 16)
    PLUG(PaintPixel, paintPixel, 17)
    PLUG(Alphabet, alphabet, 18);

//    testJson.loadJson();

    badgeService.setPaintPixel(&paintPixel);
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
    animationProgram.setProgram(0);
    animator.start();
}

