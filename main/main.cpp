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
#include "animations/SmearAnimation.h"
#include "animations/display.h"

#include <stdio.h>

extern "C" {
	void app_main(void);
}

#define LED_STRIP_TAG "LED STRIP"

#define LED_STRIP_LENGTH 64U
#define LED_STRIP_RMT_INTR_NUM 19U

static struct led_color_t led_strip_buf_1[LED_STRIP_LENGTH];
static struct led_color_t led_strip_buf_2[LED_STRIP_LENGTH];
//static struct led_strip_t ledStrip = {
//	.rgb_led_type = RGB_LED_TYPE_WS2812,
//	.rmt_channel = RMT_CHANNEL_1,
//	.rmt_interrupt_num = LED_STRIP_RMT_INTR_NUM,
//	.gpio = GPIO_NUM_21,
//	.led_strip_buf_1 = led_strip_buf_1,
//	.led_strip_buf_2 = led_strip_buf_2,
//	.led_strip_length = LED_STRIP_LENGTH
//};
static struct led_strip_t ledStrip = { RGB_LED_TYPE_WS2812, LED_STRIP_LENGTH };

//static SmearAnimation animation(&ledStrip);

Display display(&ledStrip);
static SmearAnimation animation(&display);

#include "soc/timer_group_struct.h"
#include "driver/timer.h"

#define TIMER_DIVIDER         16  //  Hardware timer clock divider
#define TIMER_SCALE           (TIMER_BASE_CLK / TIMER_DIVIDER)  // convert counter value to seconds
//#define TIMER_INTERVAL0_SEC   (3.4179) // sample test interval for the first timer
#define TIMER_INTERVAL0_SEC   (0.100) // sample test interval for the first timer
#define TIMER_INTERVAL1_SEC   (5.78)   // sample test interval for the second timer
#define TEST_WITHOUT_RELOAD   0        // testing will be done without auto reload
#define TEST_WITH_RELOAD      1        // testing will be done with auto reload

static void drawFrame() {
	static uint8_t r = 0;
//	led_strip_set_pixel_rgb(&ledStrip, 0, r, 20, 20);
//	led_strip_set_pixel_rgb(&ledStrip, 1, 20, r, 20);
//	led_strip_show(&ledStrip);
//	animation.ledStrip = &ledStrip;
//	led_strip_set_pixel_rgb(animation.ledStrip, 0, r, 20, 20);
//	led_strip_set_pixel_rgb(animation.ledStrip, 1, 20, r, 20);
//	led_strip_show(animation.ledStrip);
	r = (r + 3) % 256;
}

/*
 * Timer group0 ISR handler
 *
 * Note:
 * We don't call the timer API here because they are not declared with IRAM_ATTR.
 * If we're okay with the timer irq not being serviced while SPI flash cache is disabled,
 * we can allocate this interrupt without the ESP_INTR_FLAG_IRAM flag and use the normal API.
 */
void IRAM_ATTR timer_group0_isr(void *para)
{
    int timer_idx = (int) para;

    /* Retrieve the interrupt status and the counter value
       from the timer that reported the interrupt */
    uint32_t intr_status = TIMERG0.int_st_timers.val;
    TIMERG0.hw_timer[timer_idx].update = 1;
    uint64_t timer_counter_value =
        ((uint64_t) TIMERG0.hw_timer[timer_idx].cnt_high) << 32
        | TIMERG0.hw_timer[timer_idx].cnt_low;

    /* Prepare basic event data
       that will be then sent back to the main program task */
//    timer_event_t evt;
//    evt.timer_group = 0;
//    evt.timer_idx = timer_idx;
//    evt.timer_counter_value = timer_counter_value;

    /* Clear the interrupt
       and update the alarm time for the timer with without reload */
    if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_0) {
//        evt.type = TEST_WITHOUT_RELOAD;
        TIMERG0.int_clr_timers.t0 = 1;
        timer_counter_value += (uint64_t) (TIMER_INTERVAL0_SEC * TIMER_SCALE);
        TIMERG0.hw_timer[timer_idx].alarm_high = (uint32_t) (timer_counter_value >> 32);
        TIMERG0.hw_timer[timer_idx].alarm_low = (uint32_t) timer_counter_value;
    } else if ((intr_status & BIT(timer_idx)) && timer_idx == TIMER_1) {
//        evt.type = TEST_WITH_RELOAD;
        TIMERG0.int_clr_timers.t1 = 1;
    } else {
//        evt.type = -1; // not supported even type
    }

    /* After the alarm has been triggered
      we need enable it again, so it is triggered the next time */
    TIMERG0.hw_timer[timer_idx].config.alarm_en = TIMER_ALARM_EN;

    /* Now just send the event data back to the main program task */
//    xQueueSendFromISR(timer_queue, &evt, NULL);
    animation.drawFrame();
}

/*
 * Initialize selected timer of the timer group 0
 *
 * timer_idx - the timer number to initialize
 * auto_reload - should the timer auto reload on alarm?
 * timer_interval_sec - the interval of alarm to set
 */
static void example_tg0_timer_init(timer_idx_t timer_idx,
    bool auto_reload, double timer_interval_sec)
{
    /* Select and initialize basic parameters of the timer */
    timer_config_t config;
    config.divider = TIMER_DIVIDER;
    config.counter_dir = TIMER_COUNT_UP;
    config.counter_en = TIMER_PAUSE;
    config.alarm_en = TIMER_ALARM_EN;
    config.intr_type = TIMER_INTR_LEVEL;
    config.auto_reload = auto_reload;
    timer_init(TIMER_GROUP_0, timer_idx, &config);

    /* Timer's counter will initially start from value below.
       Also, if auto_reload is set, this value will be automatically reload on alarm */
    timer_set_counter_value(TIMER_GROUP_0, timer_idx, 0x00000000ULL);

    /* Configure the alarm value and the interrupt on alarm. */
    timer_set_alarm_value(TIMER_GROUP_0, timer_idx, timer_interval_sec * TIMER_SCALE);
    timer_enable_intr(TIMER_GROUP_0, timer_idx);
    timer_isr_register(TIMER_GROUP_0, timer_idx, timer_group0_isr,
        (void *) timer_idx, ESP_INTR_FLAG_IRAM, NULL);

    timer_start(TIMER_GROUP_0, timer_idx);
}


void main_led_task(void *args) {


//	TickType_t lastTick = xTaskGetTickCount();
//	const TickType_t period = 10;
//
	while (1) {
//		drawFrame();
		vTaskDelay(50 / portTICK_PERIOD_MS);
	}
}

//void app_main()
//{
//    printf("Hello world!\n");
//   xTaskCreate(&main_led_task, "man_led_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
//}

void app_main(void)
{
    nvs_flash_init();

    ESP_LOGI(LED_STRIP_TAG, "initializing\n");

    ledStrip.rmt_channel = RMT_CHANNEL_1;
    ledStrip.rmt_interrupt_num = LED_STRIP_RMT_INTR_NUM;
    ledStrip.gpio = GPIO_NUM_21;
    ledStrip.led_strip_buf_1 = led_strip_buf_1;
    ledStrip.led_strip_buf_2 = led_strip_buf_2;
	ledStrip.access_semaphore = xSemaphoreCreateBinary();
	bool ok = led_strip_init(&ledStrip);
    ESP_LOGI(LED_STRIP_TAG, "init status %d\n", ok);
//    	animation.ledStrip = &ledStrip;

//	led_strip_set_pixel_rgb(&ledStrip, 0, 0, 210, 0);
//	led_strip_show(&ledStrip);

    example_tg0_timer_init(TIMER_0, TEST_WITHOUT_RELOAD, TIMER_INTERVAL0_SEC);

	TaskHandle_t main_task_handle;
    BaseType_t task_created = xTaskCreate(main_led_task,
                                            "main_led_task",
                                            ESP_TASK_MAIN_STACK,
                                            NULL,
                                            ESP_TASK_MAIN_PRIO,
                                            &main_task_handle);

    (void)task_created;
    vTaskDelete(NULL);

}

