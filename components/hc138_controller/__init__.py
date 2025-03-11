import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import output
from esphome.const import CONF_ID, CONF_PIN

hc138_ns = cg.esphome_ns.namespace('hc138_controller')
HC138Controller = hc138_ns.class_('HC138Controller', output.BinaryOutput, cg.Component)

CONF_A0_PIN = "a0_pin"
CONF_A1_PIN = "a1_pin"
CONF_A2_PIN = "a2_pin"
CONF_EN_PIN = "en_pin"
CONF_CHANNELS = "channels"

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HC138Controller),
    cv.Required(CONF_A0_PIN): cv.use_id(InternalGPIOPin),
    cv.Required(CONF_A1_PIN): cv.use_id(InternalGPIOPin),
    cv.Required(CONF_A2_PIN): cv.use_id(InternalGPIOPin),
    cv.Required(CONF_EN_PIN): cv.use_id(InternalGPIOPin),
    cv.Optional(CONF_CHANNELS, default=8): cv.int_range(min=1, max=8),
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    
    a0_pin = yield cg.gpio_pin_expression(config[CONF_A0_PIN])
    a1_pin = yield cg.gpio_pin_expression(config[CONF_A1_PIN])
    a2_pin = yield cg.gpio_pin_expression(config[CONF_A2_PIN])
    en_pin = yield cg.gpio_pin_expression(config[CONF_EN_PIN])
    
    cg.add(var.set_pins(a0_pin, a1_pin, a2_pin, en_pin))
    cg.add(var.set_channel_count(config[CONF_CHANNELS]))
