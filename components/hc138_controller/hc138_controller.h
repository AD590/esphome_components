#pragma once
#include "esphome.h"

namespace esphome {
namespace hc138_controller {

class HC138Controller : public Component, public output::BinaryOutput {
 public:
  void set_pins(uint8_t a0_pin, uint8_t a1_pin, uint8_t a2_pin, uint8_t en_pin);
  void set_channel_count(uint8_t channels);
  
  void setup() override;
  void write_state(bool state) override;
  
 protected:
  void update_channel_();
  
  uint8_t a0_pin_;
  uint8_t a1_pin_;
  uint8_t a2_pin_;
  uint8_t en_pin_;
  uint8_t channels_ = 8;
  uint8_t current_channel_ = 0xFF;
};

}  // namespace hc138_controller
}  // namespace esphome
