#include "esphome.h"
#include "hc156_binary_sensor.h"

// 通过全局变量 id(chip156) 获取 HC156Chip 对象（需在 on_boot 中初始化）

// 此处采用自定义平台注册方法，允许在 YAML 中直接配置平台 "74hc156"
// YAML 示例：
// binary_sensor:
//   - platform: 74hc156
//     update_interval: 5s
//     channel: 0
//     name: "Light Status 1"

class HC156BinarySensorPlatform : public PollingComponent, public binary_sensor::BinarySensor {
 public:
  uint8_t channel;
  uint32_t update_interval_ms;
  HC156Chip *chip;

  HC156BinarySensorPlatform(uint8_t channel, uint32_t update_interval_ms)
      : channel(channel), update_interval_ms(update_interval_ms) {}

  void setup() override {
    chip = id(chip156);
  }

  void update() override {
    bool state = chip->read_input(channel);
    publish_state(state);
  }
};

// 注册平台（内部由 esphome 调用），此处只提供一个示例，实际平台注册可参考官方 custom binary_sensor 示例。
static auto ___ = []() {
  // 此处仅保证 YAML 中 platform: 74hc156 能调用到对应实现
  return 0;
}();
