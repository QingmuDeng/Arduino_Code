int const T1 = 5;
int const T2 = 6;
int const onoff = 4;
int const dir = 3;
byte previous = LOW;
byte buttonprevious = LOW;
byte state = LOW;
byte spin = LOW;
unsigned long Time[2] = {0, 0};
long debounce = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(T1, OUTPUT);
  pinMode(T2, OUTPUT);
  pinMode(onoff, INPUT);
  pinMode(dir, INPUT);
  digitalWrite(T1, LOW);
  digitalWrite(T2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Switch = digitalRead(onoff);
  if(Switch == HIGH && previous == LOW && millis() - Time[0] > debounce) {
    if(state == LOW) {
      state = HIGH;
      Serial.println("The circuit is closed");
    }else if(state == HIGH) {
      state = LOW;
      Serial.println("The circuit is opened");
    }
    Time[0] = millis();
  }
  previous = Switch;

  if(state == HIGH) {
    int button = digitalRead(dir);
    if(button == HIGH && buttonprevious == LOW && millis() - Time[1] > debounce) {
      if(spin == LOW) {
        spin = HIGH;
        digitalWrite(T1, HIGH);
        digitalWrite(T2, LOW);
        Serial.println("Blue");
      }else if(spin == HIGH) {
        spin = LOW;
        digitalWrite(T1, LOW);
        digitalWrite(T2, HIGH);
        Serial.println("Red");
      }
      Time[1] = millis();
    }
    buttonprevious = button;
  }else{
   digitalWrite(T1, LOW);
   digitalWrite(T2, LOW);
  }
}
