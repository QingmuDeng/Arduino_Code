unsigned long Time = 0;
float RPM, period;
int reading, previous;

void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(2);
  //Serial.println(reading);
  Serial.println(micros() - Time);
  if(reading == 0 && previous == 1){
    Time = micros();
  }
  previous = reading;
  //Serial.println(Time);
    /*period = (micros() - Time);
    Time = micros();
    Serial.print(period);
  }else{
    Serial.println("false");
  }
  RPM = 60000000.0 / (float)period;
  Serial.print("   The rotational speed is ");
  Serial.print(RPM);
  Serial.println(" round(s) per minute.");*/
}
