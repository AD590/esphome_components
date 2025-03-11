#include "hc138_controller.h"

namespace esphome {
namespace hc138_controller {

void HC138Controller::set_pins(uint8_t a0_pin, uint8_t a1_pin, uint8_t a2_pin, uint8_t en_pin) {
  a0_pin_ = a0_pin;
  a1_pin_ = a1_pin;
  a2_pin_ = a2_pin;
  en_pin_ = en_pin;
}

void HC138Controller::set_channel_count(uint8_t channels) {
  channels_ = std::min(channels, static_cast<uint8_t>(8));
}

void HC138Controller::setup() {
  pinMode(a0_pin_, OUTPUT);
  pinMode(a1_pin_, OUTPUT);
  pinMode(a2_pin_, OUTPUT);
  pinMode(en_pin_, OUTPUT);
  digitalWrite(en_pin_, LOW);  // 初始禁用输出
}

void HC138Controller::write_state(bool state) {
  if (!state) {
    digitalWrite(en_pin_, LOW);
    return;
  }
  
  if (current_channel_ >= channels_) {
    ESP_LOGE("HC138", "Invalid channel %d (max %d)", current_channel_, channels_);
    return;
  }
  
  digitalWrite(a0_pin_, (current_channel_ & 0x01));
  digitalWrite(a1_pin_, (current_channel_ & 0x02) >> 1);
  digitalWrite(a2_pin_, (current_channel_ & 0x04) >> 2);
  digitalWrite(en_pin_, HIGH);
}

}  // namespace hc138_controller
}  // namespace esphome
