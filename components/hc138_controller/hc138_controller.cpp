#include "hc138_controller.h"

HC138_Output::HC138_Output(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t en) {
  pins_[0] = a0;
  pins_[1] = a1; 
  pins_[2] = a2;
  en_pin_ = en;
}

void HC138_Output::setup() {
  for(int i=0; i<3; i++) pinMode(pins_[i], OUTPUT);
  pinMode(en_pin_, OUTPUT);
  digitalWrite(en_pin_, HIGH);
}

OutputChannel* HC138_Output::get_channel(uint8_t ch) {
  return new OutputChannel([this, ch](bool state) {
    if(ch != current_ch_) {
      digitalWrite(en_pin_, LOW); // 关闭输出
      digitalWrite(pins_[0], (ch & 0x01));
      digitalWrite(pins_[1], (ch & 0x02) >> 1);
      digitalWrite(pins_[2], (ch & 0x04) >> 2);
      digitalWrite(en_pin_, HIGH); // 启用新通道
      current_ch_ = ch;
      delay(1); // 确保继电器稳定
    }
  });
}
