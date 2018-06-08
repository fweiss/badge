#include "display.h"
#include "led_strip/led_strip.h"

Display::Display() {
    rmt_channel_t rmt_channel = RMT_CHANNEL_1;
    int rmt_interrupt_num = 19U;
    gpio_num_t gpio = GPIO_NUM_21;
    bool showing_buf_1 = false;

	ledStrip = new led_strip_t{RGB_LED_TYPE_WS2812, 64, rmt_channel, rmt_interrupt_num, gpio, showing_buf_1, led_strip_buf_1, led_strip_buf_2};
	ledStrip->access_semaphore = xSemaphoreCreateBinary();
	bool ok = led_strip_init(ledStrip);
	this->brightness = 25;
}

Display::Display(led_strip_t *ledStrip) {
	this->ledStrip = ledStrip;
	this->brightness = 50;
}

void Display::clear() {

}

void Display::setPixelRgb(uint16_t p, uint8_t r, uint8_t g, uint8_t b) {
	uint8_t scaledRed = (r * brightness) / 100;
	uint8_t scaledGreen = (g * brightness) / 100;
	uint8_t scaledBlue = (b * brightness) / 100;
	led_strip_set_pixel_rgb(ledStrip, p, scaledRed, scaledGreen, scaledBlue);
}

void Display::update() {
	led_strip_show(ledStrip);
}
