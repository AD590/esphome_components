import esphome.codegen as cg
from esphome.components.binary_sensor import binary_sensor_ns

HC165Reader = binary_sensor_ns.class_('HC165Reader', cg.PollingComponent)

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(HC165Reader),
    cv.Required('pl_pin'): cv.use_id(InternalGPIOPin),
    cv.Required('cp_pin'): cv.use_id(InternalGPIOPin),
    cv.Required('data_pin'): cv.use_id(InternalGPIOPin),
    cv.Optional('update_interval', default='100ms'): cv.update_interval,
}).extend(cv.COMPONENT_SCHEMA)

def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    yield cg.register_component(var, config)
    
    pl_pin = yield cg.gpio_pin_expression(config['pl_pin'])
    cp_pin = yield cg.gpio_pin_expression(config['cp_pin'])
    data_pin = yield cg.gpio_pin_expression(config['data_pin'])
    
    cg.add(var.setup(pl_pin, cp_pin, data_pin))
