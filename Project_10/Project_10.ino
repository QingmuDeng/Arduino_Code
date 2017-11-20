byte readingSwitch, readingDIR, voltageOut;
byte previousSwitch = 0;
unsigned long timeSwitch = 0;
byte stateSwitch = 0;
byte previousDIR = 0;
unsigned long timeDIR = 0;
byte stateDIR = 0;
int potentReading;
long debounce = 200;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  pinMode(9, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  readingSwitch = digitalRead(12);
  readingDIR = digitalRead(11);
  potentReading = analogRead(A0);
  voltageOut = map(potentReading, 0, 1023, 0, 255);
  
  if(previousSwitch == 0 && readingSwitch == 1 && millis() - timeSwitch > debounce) {
    if(stateSwitch == HIGH){
      stateSwitch = LOW;
    }else if(stateSwitch == LOW){
      stateSwitch = HIGH;
    }
    timeSwitch = millis();
  }
  if(previousDIR == 0 && readingDIR == 1 && millis() - timeDIR > debounce) {
    if(stateDIR == HIGH){
      stateDIR = LOW;
    }else if(stateDIR == LOW){
      stateDIR = HIGH;
    }
    timeDIR = millis();
  }
  previousDIR = readingDIR;
  previousSwitch = readingSwitch;
  if(stateDIR == HIGH){
    digitalWrite(7, HIGH);
    digitalWrite(2, LOW);
  }else if(stateDIR == LOW){
    digitalWrite(7, LOW);
    digitalWrite(2, HIGH);
  }
  if(stateSwitch == HIGH){
    //Serial.println(potentReading);
    analogWrite(9, voltageOut);
  }else if(stateSwitch == LOW){
    analogWrite(9, LOW);
  }
  
}
