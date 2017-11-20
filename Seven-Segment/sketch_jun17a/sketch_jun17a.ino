byte _1 = 5;
byte _2 = 6;
byte _4 = 7;
byte _5 = 8;
byte _6 = 12;
byte _7 = 11;
byte _9 = 10;
byte _10 = 9;
int debounce = 500;

void setup() {
  // put your setup code here, to run once:
  for(int i = 5; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()) {
    uint8_t number = Serial.read() - 48;
    if(number == 0) {
      writeZero();
    }else if(number == 1) {
      writeOne();
    }else if(number == 2) {
      writeTwo();
    }else if(number == 3) {
      writeThree();
    }else if(number == 4) {
      writeFour();
    }else if(number == 5) {
      writeFive();
    }else if(number == 6) {
      writeSix();
    }else if(number == 7) {
      writeSeven();
    }else if(number == 8) {
      writeEight();
    }else if(number == 9) {
      writeNine();
    }
  }
}



void writeOne() {
  //Display the Number 1
  digitalWrite(_1, LOW);
  digitalWrite(_2, LOW);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, LOW);
  digitalWrite(_9, LOW);
  digitalWrite(_10, LOW);
  delay(debounce);
}
void writeTwo() {  
  //Display the Number 2
  digitalWrite(_1, HIGH);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, LOW);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, LOW);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeThree() {
  //Display the Number 3
  digitalWrite(_1, LOW);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, LOW);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeFour() {
  //Display the Number 4
  digitalWrite(_1, LOW);
  digitalWrite(_2, LOW);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, LOW);
  digitalWrite(_9, HIGH);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeFive() {
  //Display the Number 5
  digitalWrite(_1, LOW);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, LOW);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, HIGH);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeSix() {
  //Display the Number 6
  digitalWrite(_1, HIGH);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, LOW);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, HIGH);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeSeven() {
  //Display the Number 7
  digitalWrite(_1, LOW);
  digitalWrite(_2, LOW);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, LOW);
  digitalWrite(_10, LOW);
  delay(debounce);
}
void writeEight() {
  //Display the Number 8
  digitalWrite(_1, HIGH);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, HIGH);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeNine() {
  //Display the Number 9
  digitalWrite(_1, LOW);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, HIGH);
  digitalWrite(_10, HIGH);
  delay(debounce);
}
void writeZero() {
  //Display the Number 0
  digitalWrite(_1, HIGH);
  digitalWrite(_2, HIGH);
  digitalWrite(_4, HIGH);
  digitalWrite(_5, LOW);
  digitalWrite(_6, HIGH);
  digitalWrite(_7, HIGH);
  digitalWrite(_9, HIGH);
  digitalWrite(_10, LOW);
  delay(debounce);
}
void clearDisplay() {
  digitalWrite(_1, LOW);
  digitalWrite(_2, LOW);
  digitalWrite(_4, LOW);
  digitalWrite(_5, LOW);
  digitalWrite(_6, LOW);
  digitalWrite(_7, LOW);
  digitalWrite(_9, LOW);
  digitalWrite(_10, LOW);
}
