int note[] = {262, 294, 330, 349};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorInput = analogRead(A0);
  //Serial.println(sensorInput);

  if(sensorInput == 1023) {
    tone(9, note[0]);
  } else if(sensorInput >= 990 && sensorInput <= 1010) {
    tone(9, note[1]);
  } else if(sensorInput >= 500 && sensorInput <= 520) {
    tone(9, note[2]);
  }else if(sensorInput >= 3 && sensorInput <= 30) {
    tone(9, note[3]);
  } else {
    noTone(9);
  }
  
}
