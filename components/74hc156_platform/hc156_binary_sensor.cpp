#include "hc156_binary_sensor.h"

HC156BinarySensor::HC156BinarySensor(HC156Chip *chip, uint8_t channel, uint32_t update_interval)
    : PollingComponent(update_interval), chip_(chip), channel_(channel) {}

void HC156BinarySensor::update() {
  bool state = chip_->read_input(channel_);
  publish_state(state);
}
