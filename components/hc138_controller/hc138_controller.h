#include "esphome.h"

class HC138_Output : public Component {
public:
  HC138_Output(uint8_t a0, uint8_t a1, uint8_t a2, uint8_t en);
  void setup() override;
  OutputChannel* get_channel(uint8_t ch);

private:
  uint8_t pins_[3];
  uint8_t en_pin_;
  uint8_t current_ch_ = 0xFF;
};
