#include "esphome.h"
#include <Adafruit_CCS811.h>
#include "SparkFun_Si7021_Breakout_Library.h"

using namespace esphome;

class MySensors : public PollingComponent {
 public:

  Adafruit_CCS811 co2 = Adafruit_CCS811();
  Weather hum = Weather();

  sensor::Sensor co2_sensor = sensor::Sensor();
  sensor::Sensor tvoc_sensor = sensor::Sensor();
  sensor::Sensor hum_sensor = sensor::Sensor();
  sensor::Sensor temp_sensor = sensor::Sensor();

  // constructor
  MySensors() : PollingComponent(15000) {}

  void setup() override {
    bool status = co2.begin();
    while(!co2.available());
    float temp = co2.calculateTemperature();
    co2.setTempOffset(temp - 25.0);

    status = hum.begin();
  }

  void update() override {
    co2.readData();
    co2_sensor.publish_state(co2.geteCO2());
    tvoc_sensor.publish_state(co2.getTVOC());

    hum_sensor.publish_state(hum.getRH());
    temp_sensor.publish_state(hum.readTemp());
  }
};
