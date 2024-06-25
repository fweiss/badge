#include "matrix.h"

#include "esp_log.h"

static const char TAG[] = "Matrix";

Matrix::Matrix(gpio_num_t gpioPin, size_t size) : size(size) {
    esp_err_t status;

    grbPixels = (typeof(grbPixels[0])*)malloc(size * bytesPerPixel);
    if (grbPixels == 0) {
        ESP_LOGE(TAG, "alloc pixel buffer failed: size %d", size * bytesPerPixel);
        return;
    }

    channel = NULL;
    rmt_tx_channel_config_t config = {
        .gpio_num = gpioPin,
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = tickResolutionHz,
        .mem_block_symbols = 64,
        .trans_queue_depth = 4,
    };
    // config.flags.with_dma = 1; // depends on chip
    ESP_ERROR_CHECK(rmt_new_tx_channel(&config, &channel));

    rmt_bytes_encoder_config_t bytesEncoderConfig{
        .bit0{
            .duration0 = fromMicros(0.350),
            .level0 = 1,
            .duration1 = fromMicros(0.800),
            .level1 = 0,
        },
        .bit1{
            .duration0 = fromMicros(0.700),
            .level0 = 1,
            .duration1 = fromMicros(0.600),
            .level1 = 0,
        },
        .flags = {
            .msb_first = 1, // WS2812 data is sent MSB first
        },
    };
    ESP_ERROR_CHECK(rmt_new_bytes_encoder(&bytesEncoderConfig, &encoder));
    ESP_LOGI(TAG, "encoder created %p", encoder);

    ESP_ERROR_CHECK(rmt_enable(channel));
}

// destructor
Matrix::~Matrix() {
    // stop the channel
    // free the channel
    // free the channel
    // free the encoder
    //  free the pixel buffer
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
        ESP_LOGW(TAG, "setPixelRgb: index out of range %lu", index);
        return;
    }
    uint32_t start = index * 3;
    // GRB order as per the device
    grbPixels[start + 0] = green & 0xFF;
    grbPixels[start + 1] = red & 0xFF;
    grbPixels[start + 2] = blue & 0xFF;
}

uint32_t Matrix::getPixelRgb(uint16_t index) {
    if (grbPixels == 0) {
        ESP_LOGW(TAG, "could not get pixel, no rgbPixels allocated");
        return 0;
    }
    if (index >= size) {
        ESP_LOGW(TAG, "getPixelRgb: index out of range %d", index);
        return 0;
    }
    uint32_t start = index * 3;
    const uint8_t r = grbPixels[start + 1];
    const uint8_t g = grbPixels[start + 0];
    const uint8_t b = grbPixels[start + 2];
    return (r << 16) | (g << 8) | (b << 0);
}

void Matrix::show() {
    esp_err_t status;

    if (grbPixels == 0) {
        ESP_LOGW(TAG, "could not show pixels, no rgbPixels allocated");
        return;
    }

//    sendReset();

    bool wait_tx_done = true;
    rmt_transmit_config_t transmitConfig{};
    status = rmt_transmit(channel, encoder, grbPixels, size * bytesPerPixel, &transmitConfig);
    if (status != ESP_OK) {
        ESP_LOGW(TAG, "RMT write sample failed: %d", status);
    }
    rmt_tx_wait_all_done(channel, 100);
}

// some have reported that since 2017, WS2812B requires 300 us reset low
void Matrix::sendReset() {
    // esp_err_t status;

    // rmt_item32_t rmt_item[2];
    // rmt_item[0].duration0 = 1000;
    // rmt_item[0].level0 = 1;
    // rmt_item[0].duration1 = 10000; // 500 us
    // rmt_item[0].level1 = 0;
    // rmt_item[1].duration0 = 10000;
    // rmt_item[1].level0 = 0;
    // rmt_item[1].duration1 = 1000;
    // rmt_item[1].level1 = 1;

    // bool wait_tx_done = true;
    // status = rmt_write_items(channel, rmt_item, 2, wait_tx_done);
    // if (status != ESP_OK) {
    //     ESP_LOGW(TAG, "rmt write items failed: %d", status);
    // }
//    ESP_LOGI(TAG, "reset pulse sent");
}
