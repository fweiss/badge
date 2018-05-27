#include "freertos/FreeRTOS.h"
#include "led_strip/led_strip.h"

class Display {
private:
	struct led_strip_t *ledStrip;
	uint8_t brightness;
protected:
public:
	Display();
	Display(led_strip_t *ledString);
	void clear();
	void update();
	void setPixelRgb(uint16_t p, uint8_t r, uint8_t g, uint8_t b);
};
