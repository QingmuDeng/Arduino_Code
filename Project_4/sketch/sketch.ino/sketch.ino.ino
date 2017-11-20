int const rInput = A0;
int const bInput = A1;
int const gInput = A2;

int sensorValueR, sensorValueB, sensorValueG;
int rValue, bValue, gValue;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  for(int i = 9; i < 12; i++) {
    pinMode(i, OUTPUT);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValueR = analogRead(A0);
  delay(5);
  sensorValueB = analogRead(A1);
  delay(5);
  sensorValueG = analogRead(A2);
  delay(5);
  rValue = sensorValueR/4;
  bValue = sensorValueB/4;
  gValue = sensorValueG/4;
  /*Serial.print("temp: ");
  Serial.println(sensorValueT);
  Serial.print("\tG: ");
  Serial.print(gValue);
  Serial.print("\tB: ");
  Serial.println(bValue);*/

  analogWrite(11, rValue);
  analogWrite(10, bValue);
  analogWrite(9, gValue);
}
