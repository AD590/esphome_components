#pragma once
#include "esphome.h"

class HC156Chip : public Component {
 public:
  // 构造函数：参数依次为 S0, S1, 数据0, 数据1 引脚
  HC156Chip(uint8_t sel0, uint8_t sel1, uint8_t data_pin0, uint8_t data_pin1);

  void setup() override;
  // 读取指定通道（0~7）的状态
  bool read_input(uint8_t channel);

 protected:
  uint8_t sel0_;
  uint8_t sel1_;
  uint8_t data_pin0_;
  uint8_t data_pin1_;
};
