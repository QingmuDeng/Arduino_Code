//int const potentIn = A0;
int potentValue;
byte reading, voltageOutput;
byte previous = LOW;
byte state = LOW;
unsigned long Time = 0;
long debounce = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(11, INPUT);
  pinMode(5, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  potentValue = analogRead(A0);
  voltageOutput = map(potentValue, 0, 1023, 0, 255);
  reading = digitalRead(11);
  
  if (previous == LOW && reading == HIGH && millis() - Time > debounce) {
    if(state == HIGH){
      state = LOW;
    }else if(state == LOW) {
      state = HIGH;
    }
    Time = millis();
  }
  if(state == HIGH){
    analogWrite(5, voltageOutput);
  }else if(state == LOW) {
    analogWrite(5, LOW);
  }

  previous = reading;
}
