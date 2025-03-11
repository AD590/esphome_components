#include "esphome.h"

class HC165Reader : public PollingComponent, public Parented<App> {
public:
  HC165Reader(uint8_t pl_pin, uint8_t cp_pin, uint8_t data_pin) 
    : PollingComponent(100),  // 默认100ms轮询
      pl_pin_(pl_pin),
      cp_pin_(cp_pin),
      data_pin_(data_pin) {}

  void setup() override {
    pinMode(pl_pin_, OUTPUT);
    pinMode(cp_pin_, OUTPUT);
    pinMode(data_pin_, INPUT);
    digitalWrite(pl_pin_, HIGH);
  }

  void update() override {
    // 并行加载数据
    digitalWrite(pl_pin_, LOW);
    delayMicroseconds(5);
    digitalWrite(pl_pin_, HIGH);
    
    // 移位读取
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
      data |= (digitalRead(data_pin_) << (7 - i));
      digitalWrite(cp_pin_, HIGH);
      delayMicroseconds(1);
      digitalWrite(cp_pin_, LOW);
    }

    // 更新状态
    for (int i = 0; i < 8; i++) {
      sensors_[i]->publish_state((data >> i) & 0x01);
    }
  }

  BinarySensor* get_sensor(uint8_t index) {
    return sensors_[index];
  }

private:
  uint8_t pl_pin_, cp_pin_, data_pin_;
  BinarySensor* sensors_[8] = {
    new BinarySensor(), new BinarySensor(), new BinarySensor(), new BinarySensor(),
    new BinarySensor(), new BinarySensor(), new BinarySensor(), new BinarySensor()
  };
};
