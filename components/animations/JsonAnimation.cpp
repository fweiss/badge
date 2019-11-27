#include "JsonAnimation.h"

#include "cJSON.h"

#include <vector>
#include <string>

#include "esp_log.h"

#define LOG_TAG "JsonAnimation"

static std::vector<std::vector<uint32_t>> zz;

JsonAnimation::JsonAnimation(Display &display) : BitmapAnimation(display, zz) {

}

static const char* json2 = R"(["0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0x2c9f0a","0xe5eca7","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x2c9f0a","0xeca7ec","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x97c7dd","0x2c9f0a","0x2c9f0a","0x2c9f0a","0xf74747","0x2c9f0a","0x738aea","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x2c9f0a","0x97c7dd","0x97c7dd","0x97c7dd","0x9f530a","0x9f530a","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x97c7dd","0x9f530a","0x9f530a","0x97c7dd","0x97c7dd","0x97c7dd"])";

// problems
// std:stoul
// no hex numbers allowed in JSON


void JsonAnimation::loadJson() {
    const char json[] = "[0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0x2c9f0a,0xe5eca7,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x2c9f0a,0xeca7ec,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x97c7dd,0x2c9f0a,0x2c9f0a,0x2c9f0a,0xf74747,0x2c9f0a,0x738aea,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x2c9f0a,0x97c7dd,0x97c7dd,0x97c7dd,0x9f530a,0x9f530a,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x97c7dd,0x9f530a,0x9f530a,0x97c7dd,0x97c7dd,0x97c7dd]";
    cJSON *root = cJSON_Parse(json2);
    cJSON_GetArraySize(root);
    ESP_LOGI(LOG_TAG, "parsed json: size: %d", cJSON_GetArraySize(root));
    std::vector<uint32_t> *frame = new std::vector<uint32_t>(64);
    for (cJSON *jsonFrame = root; jsonFrame; jsonFrame = jsonFrame->next) {
//        uint32_t v = std::stoul(jsonFrame->valueint, nullptr, 0);
//        frame->push_back(v);
    }
    zz.push_back(*frame);
    cJSON_Delete(root);
}
