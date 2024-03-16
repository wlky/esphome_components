import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, uart
from esphome.const import (
    STATE_CLASS_MEASUREMENT,
    UNIT_PERCENT,
    ICON_WATER_PERCENT,    
    DEVICE_CLASS_WATER,
)

DEPENDENCIES = ["uart"]

aj_sr04m_ns = cg.esphome_ns.namespace("aj_sr04m")
AJ_SR04M_Sensor = aj_sr04m_ns.class_(
    "AJ_SR04M_Sensor", sensor.Sensor, cg.PollingComponent, uart.UARTDevice
)

CONFIG_SCHEMA = (
    sensor.sensor_schema(
        AJ_SR04M_Sensor,
        unit_of_measurement=UNIT_PERCENT,
        icon=ICON_WATER_PERCENT,
        accuracy_decimals=2,
        state_class=STATE_CLASS_MEASUREMENT,
    )
    .extend(uart.UART_DEVICE_SCHEMA)
    .extend(cv.polling_component_schema("60s")
    )
)


async def to_code(config):
    var = await sensor.new_sensor(config)
    await cg.register_component(var, config)
    await uart.register_uart_device(var, config)