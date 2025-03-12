#include "hc138_switch.h"

HC138Switch::HC138Switch(HC138Chip *chip, uint8_t channel)
    : chip_(chip), channel_(channel) {}

void HC138Switch::write_state(bool state) {
  chip_->set_output(channel_, state);
  publish_state(state);
}
