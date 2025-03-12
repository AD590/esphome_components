#pragma once
#include "esphome.h"
#include "hc138_chip.h"

class HC138Switch : public switch_::Switch, public Component {
 public:
  // chip：共享的 HC138Chip 对象；channel：通道号（0~7）
  HC138Switch(HC138Chip *chip, uint8_t channel);

  void write_state(bool state) override;

 protected:
  HC138Chip *chip_;
  uint8_t channel_;
};
