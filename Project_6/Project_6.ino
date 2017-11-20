int sensorValue;
int sensorLow = 1023;
int sensorHigh = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  while(millis() < 5000) {
    sensorValue = analogRead(A0);
    if(sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }else if(sensorValue < sensorHigh) {
      sensorLow =  sensorValue;
    }
  }
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  sensorValue = analogRead(A0);
  int pitch = map(sensorValue, sensorLow, sensorHigh, 50, 4000);

  tone(9, pitch,100);

  delay(10);
}

