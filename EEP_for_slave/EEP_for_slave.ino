#include<EEPROM.h>

void setup() {
  Serial.begin(9600);
  // EEPROM.write(0, 'd');
  delay(1);
  char val = EEPROM.read(0);
  Serial.print(val);
}

void loop() {
  // put your main code here, to run repeatedly:

}
