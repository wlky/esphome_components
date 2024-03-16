#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"

namespace esphome
{
  namespace aj_sr04m
  {

    class AJ_SR04M_Sensor : public sensor::Sensor, public uart::UARTDevice, public PollingComponent
    {
    public:
      void update() override;
      void dump_config() override;
    };

  } // namespace adc_mpx
} // namespace esphome
