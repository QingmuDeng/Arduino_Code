int voltageSignal;
int t = 500;
int i;
void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(2, INPUT);

  for(i = 0; i < 6; i++) {
    digitalWrite(5, 0);
    delay(100);
    digitalWrite(5, 1);
    delay(100);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  voltageSignal = digitalRead(2);
  if(voltageSignal == 0){
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    delay(t);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(t);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(t);
  } else {
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    delay(300);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    delay(300);
  }
}
