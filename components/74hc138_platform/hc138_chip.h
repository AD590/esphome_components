#pragma once
#include "esphome.h"

class HC138Chip : public Component {
 public:
  // 构造函数：参数依次为 A, B, C, E 引脚
  HC138Chip(uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinE);

  void setup() override;
  // 设置指定通道（0~7）的输出状态
  void set_output(uint8_t channel, bool state);

 protected:
  uint8_t pinA_;
  uint8_t pinB_;
  uint8_t pinC_;
  uint8_t pinE_;
  bool outputs_[8];
  void update_outputs();
};
