#include "aj_sr04m.h"

#include "esphome/core/log.h"

namespace esphome
{
  namespace aj_sr04m
  {

    static const char *TAG = "AJ_SR04M_Sensor";

    void AJ_SR04M_Sensor::dump_config()
    {
      LOG_SENSOR("", "AJ SR04M Sensor", this);
    }

    void AJ_SR04M_Sensor::update()
    {
      char frame[4];
      int pos = 0;

      float value = 0.0;

      write(0x01);
      while (available())
      {

        frame[pos] = read();
        pos++;
        if (pos == 4)
        {
          if ((frame[0] == 0xFF) /*&& ((frame[1]+frame[2])==frame[3])*/)
          {
            value = ((frame[1] << 8) + frame[2]) / 10.0;
            ESP_LOGW(TAG, "Measured: %f", value);
            value = 100.0 * ((value - 60.0) / (10 - 60)); // map(value, 60, 10, 0, 100);
            if (value > 100)
            {
              value = 100;
            }
            if (value < 0)
            {
              value = 0;
            }
            publish_state(value);
          }
          break;
        }
      }
    }

  } // namespace adc_mpx
} // namespace esphome
