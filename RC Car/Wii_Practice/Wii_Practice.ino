#include <Wire.h>
#include <ArduinoNunchuk.h>

#define BAUDRATE 19200

ArduinoNunchuk nunchuck = ArduinoNunchuk();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(BAUDRATE);
  nunchuck.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  nunchuck.update();

  Serial.print(nunchuck.analogX);
  Serial.print(' ');
  Serial.print(nunchuck.analogY);
  Serial.print(' ');
  Serial.print(nunchuck.accelX);
  Serial.print(' ');
  Serial.print(nunchuck.accelY);
  Serial.print(' ');
  Serial.print(nunchuck.accelZ);
  Serial.print(' ');
  Serial.print(nunchuck.zButton);
  Serial.print(' ');
  Serial.println(nunchuck.cButton);
  delay(100);
}
