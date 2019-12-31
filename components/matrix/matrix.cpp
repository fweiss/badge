#include "matrix.h"

#include "esp_log.h"

static const char TAG[] = "Matrix";

// these will be set by the construcotr
static uint32_t ws2812_t0h_ticks = 0;
static uint32_t ws2812_t0l_ticks = 0;
static uint32_t ws2812_t1h_ticks = 0;
static uint32_t ws2812_t1l_ticks = 0;

//typedef void (*sample_to_rmt_t)(const void *src, rmt_item32_t *dest, size_t src_size, size_t wanted_num, size_t *translated_size, size_t *item_num)
/**
 * @brief Conver RGB data to RMT format.
 *
 * @note For WS2812, R,G,B each contains 256 different choices (i.e. uint8_t)
 *
 * @param[in] src: source data, to converted to RMT format
 * @param[in] dest: place where to store the convert result
 * @param[in] src_size: size of source data
 * @param[in] wanted_num: number of RMT items that want to get
 * @param[out] translated_size: number of source data that got converted
 * @param[out] item_num: number of RMT items which are converted from source data
 */
static void IRAM_ATTR ws2812_rmt_adapter(const void *src, rmt_item32_t *dest, size_t src_size, size_t wanted_num, size_t *translated_size, size_t *item_num) {
    if (src == NULL || dest == NULL) {
        *translated_size = 0;
        *item_num = 0;
        return;
    }
    const rmt_item32_t bit0 = {{{ ws2812_t0h_ticks, 1, ws2812_t0l_ticks, 0 }}}; //Logical 0
    const rmt_item32_t bit1 = {{{ ws2812_t1h_ticks, 1, ws2812_t1l_ticks, 0 }}}; //Logical 1
    size_t size = 0;
    size_t num = 0;
    uint8_t *psrc = (uint8_t *)src;
    rmt_item32_t *pdest = dest;
    while (size < src_size && num < wanted_num) {
        for (int i = 0; i < 8; i++) {
            // MSB first
            if (*psrc & (1 << (7 - i))) {
                pdest->val =  bit1.val;
            } else {
                pdest->val =  bit0.val;
            }
            num++;
            pdest++;
        }
        size++;
        psrc++;
    }
    *translated_size = size;
    *item_num = num;
}

Matrix::Matrix(gpio_num_t gpioPin, size_t size) : size(size) {
    esp_err_t status;

    grbPixels = (typeof(grbPixels[0])*)malloc(size * bytesPerPixel);
    if (grbPixels == 0) {
        ESP_LOGE(TAG, "alloc pixel buffer failed: size %d", size * bytesPerPixel);
        return;
    }

    // RMT timing for WS2812B
    // 1=80 MHz,12.5 ns, etc
    // 4=20 MHz, i.e. 50 ns
    uint16_t clk_div = 4;

    // original led_strip
    clk_div = 8; // 100ns
    ws2812_t0h_ticks = 3;
    ws2812_t0l_ticks = 9;
    ws2812_t1h_ticks = 9;
    ws2812_t1l_ticks = 3;


    //    ws2812_t0h_ticks = 9;
    //    ws2812_t0l_ticks = 18;
    //    ws2812_t1h_ticks = 17;
    //    ws2812_t1l_ticks = 10;

    // experimental
    // divider 4 = 20 Mhz = 50 ns
//    clk_div = 4;
//    ws2812_t0h_ticks = 7;
//    ws2812_t0l_ticks = 14;
//    ws2812_t1h_ticks = 11;
//    ws2812_t1l_ticks = 10;

    rmt_config_t config = RMT_DEFAULT_CONFIG_TX(gpioPin, channel);
    config.clk_div = clk_div;
    config.tx_config.loop_en = false;
//    config.tx_config.idle_level = RMT_IDLE_LEVEL_HIGH;
//    config.tx_config.idle_output_en = true;

    status = rmt_config(&config);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "config failed: %d", status);
    }

    status = rmt_driver_install(channel, 0, 0);
    if (status != ESP_OK) {
        ESP_LOGE(TAG, "RMT drive install failed: %d", status);
    }

    status = rmt_translator_init(channel, &ws2812_rmt_adapter);
    if (status != ESP_OK) {
        ESP_LOGW(TAG, "RMT translator init failed: %d", status);
    }
}

// destructor
Matrix::~Matrix() {
    esp_err_t status = rmt_driver_uninstall(channel);
    if (status != ESP_OK) {
        ESP_LOGW(TAG, "RMT drive uninstall failed: %d", status);
    }
    if (grbPixels != 0) {
        free(grbPixels);
    }
}

void Matrix::setPixelRgb(uint32_t index, uint8_t red, uint8_t green, uint8_t blue) {
    if (grbPixels == 0) {
        ESP_LOGW(TAG, "could not set pixel, no rgbPixels allocated");
        return;
    }
    if (index >= size) {
        ESP_LOGW(TAG, "setRgbPixel: index out of range %d", index);
        return;
    }
    uint32_t start = index * 3;
    // GRB order as per the device
    grbPixels[start + 0] = green & 0xFF;
    grbPixels[start + 1] = red & 0xFF;
    grbPixels[start + 2] = blue & 0xFF;
}

void Matrix::show() {
    esp_err_t status;

    if (grbPixels == 0) {
        ESP_LOGW(TAG, "could not show pixels, no rgbPixels allocated");
        return;
    }

    sendReset();

    bool wait_tx_done = true;
    status = rmt_write_sample(channel, grbPixels, size * bytesPerPixel, wait_tx_done);
    if (status != ESP_OK) {
        ESP_LOGW(TAG, "RMT write sample failed: %d", status);
    }
}

// some have reported that since 2017, WS2812B requires 300 us reset low
void Matrix::sendReset() {
    esp_err_t status;

    rmt_item32_t rmt_item[2];
    rmt_item[0].duration0 = 1000;
    rmt_item[0].level0 = 1;
    rmt_item[0].duration1 = 10000; // 500 us
    rmt_item[0].level1 = 0;
    rmt_item[1].duration0 = 10000;
    rmt_item[1].level0 = 0;
    rmt_item[1].duration1 = 1000;
    rmt_item[1].level1 = 1;

    bool wait_tx_done = true;
    status = rmt_write_items(channel, rmt_item, 2, wait_tx_done);
    if (status != ESP_OK) {
        ESP_LOGW(TAG, "rmt write items failed: %d", status);
    }
//    ESP_LOGI(TAG, "reset pulse sent");
}
