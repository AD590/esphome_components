#pragma once
#include "esphome.h"
#include "hc156_chip.h"

class HC156BinarySensor : public PollingComponent, public binary_sensor::BinarySensor {
 public:
  // 构造函数：chip 为共享的 HC156Chip 对象；channel 为通道号（0~7）
  HC156BinarySensor(HC156Chip *chip, uint8_t channel, uint32_t update_interval);

  void update() override;

 protected:
  HC156Chip *chip_;
  uint8_t channel_;
};
