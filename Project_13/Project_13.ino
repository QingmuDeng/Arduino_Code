#include <CapacitiveSensor.h>

CapacitiveSensor capSensor1 = CapacitiveSensor(4, 2);
CapacitiveSensor capSensor2 = CapacitiveSensor(9, 8);

byte ledPin = 6;
int threshold = 1000;
unsigned long Time[2] = {0, 0};
int sensorLow = 3000;
int sensorHigh = 0;
long sensorVal, sensorVal2;
byte state = LOW;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(ledPin, HIGH);
  while(millis() < 5000) {
    sensorVal = capSensor1.capacitiveSensor(30);
    Serial.println(sensorVal);
    if(sensorVal < sensorLow) {
      sensorLow = sensorVal;
    } else if(sensorVal > sensorHigh) {
      sensorHigh = sensorVal;
    }
  }
  digitalWrite(ledPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(millis() - Time[0] > 10) {
    sensorVal2 = capSensor2.capacitiveSensor(30);
    if(sensorVal2 + 300 > sensorHigh && millis() - Time[1] > 1000) {
      if(state == LOW) {
        state = HIGH;
      } else if(state == HIGH) {
        state = LOW;
      }
      Time[1] = millis();
    }

    if(state == HIGH) {
      sensorVal = capSensor1.capacitiveSensor(30);
      //Serial.println(sensorVal);
      int outputVal = map(sensorVal, sensorLow, sensorHigh, 0, 255);
      analogWrite(ledPin, outputVal);
    } else {
      digitalWrite(ledPin, LOW);
    }
  
    /*if(sensorVal > threshold) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, LOW);
    }*/
    Time[0] = millis();
  }

}
