#include "Head.h"

void setup() {
  lcd_write(1,1,7,12,String("Idel..."));
  Serial.begin(9600);
  package_read_clear();
}

volatile float data[8];

void loop() {
  package_read_clear();
  lora_read("515");

  int senum = (int) package_read();
  switch (senum) {
    case 1:
      data[0] = package_read();
      data[1] = package_read();
      data[2] = package_read();
      data[3] = package_read();
      data[4] = package_read();
      data[5] = package_read();
      break;
  }
  lcd_write(8,1,7,16,String("ACC.X:") + String(data[0]));
  lcd_write(9,1,7,16,String("ACC.Y:") + String(data[1]));
  lcd_write(10,1,7,16,String("ACC.Z:") + String(data[2]));
  lcd_write(1,1,7,16,String("Temperature:") + String(data[3]) + "C       ");
  lcd_write(2,1,7,16,String("Altitude:") + String(data[4]) + "m       ");
  lcd_write(5,1,7,16,String("Mois:") + String(data[5]));
 
    Serial.write((char *)data, sizeof(float) * 8);
    char tail[4] = {0x00, 0x00, 0x80, 0x7f};
    Serial.write(tail, 4);
}
