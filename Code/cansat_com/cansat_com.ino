#include "Head.h"

volatile float info[8];
volatile float cache_info[8];
int iic_commu_addr = 1;
int iic_power_addr = 2;
int iic_main_addr = 3;

void setup() {
  Wire.begin(iic_commu_addr);
  Wire.onReceive(iic_receive_even);
  //Serial.begin(9600);
}

void loop() {
  package_read_clear();
  lora_read("515");
  package_write_clear();
  int infoa = package_read();
  while (infoa != 0) {
    package_write(infoa);
    infoa = package_read();
  }
  iic_write(iic_main_addr);
  
  package_read_clear(); 
  iic_read(-1);
  package_write_clear();

  int len = 0;
  info[len] = package_read();
  while (info[len] != 0) {
    len ++;
    info[len] = package_read();
  }
  
  bool flag = false;
  int i = 0;
  while (i < len) {
    if (cache_info[i] != info[i]) {
      flag = true;
      break;
    }
    i ++;
  }

  if (flag) {
    i = 0;
    while (i < len) {
      //Serial.print(" ");
      package_write(info[i]);
      cache_info[i] = info[i];
      //Serial.print(info[i]);
      i ++;
    }
    //Serial.println();
    lora_write("515");
  }
  
  delay(50);
}
