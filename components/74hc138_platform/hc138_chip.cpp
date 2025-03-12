#include "hc138_chip.h"

HC138Chip::HC138Chip(uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinE)
    : pinA_(pinA), pinB_(pinB), pinC_(pinC), pinE_(pinE) {
  for (uint8_t i = 0; i < 8; i++) {
    outputs_[i] = false;
  }
}

void HC138Chip::setup() {
  pinMode(pinA_, OUTPUT);
  pinMode(pinB_, OUTPUT);
  pinMode(pinC_, OUTPUT);
  pinMode(pinE_, OUTPUT);
  // 默认使能：低电平有效
  digitalWrite(pinE_, LOW);
  update_outputs();
}

void HC138Chip::set_output(uint8_t channel, bool state) {
  if (channel < 8) {
    outputs_[channel] = state;
    update_outputs();
  }
}

void HC138Chip::update_outputs() {
  // 示例：本例仅将通道 0 的状态输出到 A、B、C 三个引脚，
  // 实际设计中请根据电路调整，实现对各路独立控制。
  digitalWrite(pinA_, outputs_[0] ? HIGH : LOW);
  digitalWrite(pinB_, outputs_[0] ? HIGH : LOW);
  digitalWrite(pinC_, outputs_[0] ? HIGH : LOW);
}
