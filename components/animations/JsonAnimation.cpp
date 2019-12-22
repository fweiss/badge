// required with gcc 5.2.0 to access stoul in ext/vstring.h
#define _GLIBCXX_USE_C99

#include "JsonAnimation.h"

#include "cJSON.h"

#include <vector>
#include <string>

#include "esp_log.h"

#define LOG_TAG "JsonAnimation"

static const char* json2 = R"(["0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0x2c9f0a","0xe5eca7","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0xeca7ec","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x97c7dd","0x2c9f0a","0x2c9f0a","0x2c9f0a","0xf74747","0x2c9f0a","0x738aea","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x9f530a","0x9f530a","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x9f530a","0x9f530a","0x97c7dd","0x97c7dd","0x97c7dd"])";

static std::vector<std::vector<uint32_t>> zz = {
//        {0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0x2c9f0a,0xe5eca7,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0xeca7ec,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x97c7dd,0x2c9f0a,0x2c9f0a,0x2c9f0a,0xf74747,0x2c9f0a,0x738aea,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x9f530a,0x9f530a,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x9f530a,0x9f530a,0x97c7dd,0x97c7dd,0x97c7dd}
};

JsonAnimation::JsonAnimation(Display &display) : BitmapAnimation(display, zz, 1000) {
    loadJson(json2);
}

JsonAnimation::JsonAnimation(Display &display, const char *json) : BitmapAnimation(display, zz, 1000) {
    loadJson(json);
}

// problems
// std:stoul
// no hex numbers allowed in JSON


// todo check input format, size
void JsonAnimation::loadJson(const char *json) {
    zz.clear();
    cJSON *root = cJSON_Parse(json);
    ESP_LOGI(LOG_TAG, "parsed json: size: %d", cJSON_GetArraySize(root));
    std::vector<uint32_t> *frame = new std::vector<uint32_t>();

    ESP_LOGI(LOG_TAG, "root child: 0x%0x", (unsigned int)root->child);
    for (cJSON *jsonFrame = root->child; jsonFrame; jsonFrame = jsonFrame->next) {
//        ESP_LOGI(LOG_TAG, "pixel: 0x%0x", 0x08);
//        ESP_LOGI(LOG_TAG, "pixel: %s", jsonFrame->valuestring);

        std::string vs(jsonFrame->valuestring);
        uint32_t v = std::stoul(vs, nullptr, 0);
        ESP_LOGI(LOG_TAG, "pixel v: 0x%x", v);
        frame->push_back(v);
    }

//    for (cJSON *jsonFrame = root->child; jsonFrame; jsonFrame = jsonFrame->next) {
//        std::string vs("0xff0000");
//        uint32_t v = 0x00ff00; //std::stoul(vs, nullptr, 0);
//        ESP_LOGI(LOG_TAG, "pixel: 0x%0x", v);
//        frame->push_back(0x0000ff);
//    }

    ESP_LOGI(LOG_TAG, "pixels in frame: %d", frame->size());
    zz.push_back(*frame);
    cJSON_Delete(root);
    ESP_LOGI(LOG_TAG, "number of frames: %d", zz.size());
}
