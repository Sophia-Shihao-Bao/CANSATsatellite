#include "Head.h"

int iic_commu_addr = 1;
int iic_power_addr = 2;
int iic_main_addr = 3;

void setup() {
  Wire.begin(iic_power_addr);
  Wire.onReceive(iic_receive_even);
  //Serial.begin(9600);
}

void loop() {
  package_write_clear();
  package_write(2);
  package_write(sensor_read("GPS","经度") + 1);
  package_write(sensor_read("GPS","纬度") + 1);
  package_write(sensor_read("GPS","时间") + 1);
  iic_write(iic_commu_addr);
  delay(200);
  package_write_clear();
  package_write(2);
  package_write(power_read("电压"));
  package_write(power_read("电流"));
  iic_write(iic_main_addr);
  delay(500);
}
