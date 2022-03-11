#include "Head.h"

volatile int senum;
int iic_commu_addr = 1;
int iic_power_addr = 2;
int iic_main_addr = 3;

void setup() {
  Wire.begin(iic_main_addr);
  Wire.onReceive(iic_receive_even);
  GPS_SERIAL.begin(GPS_BAUD);
}

void loop() {
  /*
  package_read_clear();
  iic_read(-1);

  senum = (int) package_read();
  switch (senum) {
    case 2:
      package_write_clear();
      package_write(2);
      package_write(package_read());
      package_write(package_read());
      iic_write(iic_commu_addr);
      break;
    case 3:
      tone(8, 500);
      delay(50000);
      noTone(8);
      break;
  }
  */
  package_write_clear();
  package_write(1);
  package_write(sensor_read("MPU9250","加速度X"));
  package_write(sensor_read("MPU9250","加速度Y"));
  package_write(sensor_read("MPU9250","加速度Z"));
  package_write(sensor_read("BMP180","温度"));
  package_write(sensor_read("BMP180","海拔")); 
  package_write(sensor_read("DHT11","湿度"));
  iic_write(iic_commu_addr);
  delay(200);
}
