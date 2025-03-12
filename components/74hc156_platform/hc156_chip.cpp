#include "hc156_chip.h"

HC156Chip::HC156Chip(uint8_t sel0, uint8_t sel1, uint8_t data_pin0, uint8_t data_pin1)
    : sel0_(sel0), sel1_(sel1), data_pin0_(data_pin0), data_pin1_(data_pin1) {}

void HC156Chip::setup() {
  pinMode(sel0_, OUTPUT);
  pinMode(sel1_, OUTPUT);
  pinMode(data_pin0_, INPUT);
  pinMode(data_pin1_, INPUT);
}

bool HC156Chip::read_input(uint8_t channel) {
  if (channel < 4) {
    // 选择第一组数据（通道 0~3）
    digitalWrite(sel0_, (channel & 0x01) ? HIGH : LOW);
    digitalWrite(sel1_, (channel & 0x02) ? HIGH : LOW);
    delayMicroseconds(5);
    return digitalRead(data_pin0_);
  } else if (channel < 8) {
    uint8_t ch = channel - 4;
    // 选择第二组数据（通道 4~7）
    digitalWrite(sel0_, (ch & 0x01) ? HIGH : LOW);
    digitalWrite(sel1_, (ch & 0x02) ? HIGH : LOW);
    delayMicroseconds(5);
    return digitalRead(data_pin1_);
  }
  return false;
}
