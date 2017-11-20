#include <Servo.h>

Servo newServo;
int const potPin = A0;
int potValue;
int angle;

void setup() {
  // put your setup code here, to run once:
  newServo.attach(9);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  potValue = analogRead(potPin);
  //Serial.print(potValue);
  angle = map(potValue, 0, 1023, 0, 175);
  //Serial.print("\t");
  //Serial.println(angle);
  
  newServo.write(angle);
  delay(15);


}
