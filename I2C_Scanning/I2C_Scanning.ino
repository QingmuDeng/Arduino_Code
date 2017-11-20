#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int address = 1; address <= 128; address ++) {
    Wire.beginTransmission(address);
    if(!Wire.endTransmission()) Serial.println(address);
  }
}
