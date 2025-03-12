#include "esphome.h"
#include "hc138_switch.h"

// 使用 esphome 自定义平台注册宏
using namespace esphome;

class HC138SwitchFactory : public Component, public switch_::Switch {
 public:
  // channel 参数通过 YAML 中传入
  uint8_t channel;
  HC138Chip *chip;

  void setup() override {
    // chip 对象在全局变量中创建，此处获取引用
    chip = id(chip138);
  }

  void write_state(bool state) override {
    chip->set_output(channel, state);
    publish_state(state);
  }
};

// 通过 PLATFORM_CREATE 生成开关平台
switch_::Switch *create_hc138_switch(uint8_t channel) {
  auto *sw = new HC138Switch(id(chip138), channel);
  return sw;
}

//
// 最终注册自定义平台 "74hc138"，内部调用 HC138Switch 实现
//
class HC138SwitchPlatform : public Component {
 public:
  void setup() override {}
};

//
// 注册平台供 YAML 使用
// 注意：此处不必暴露内部实现，只需保证 YAML 中 platform: 74hc138 能正确生成对应开关实体
//
static auto ___ = []() {
  App.register_component(new HC138SwitchPlatform());
  return 0;
}();
