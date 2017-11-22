#define Cha1LED_RED A2
#define Cha2LED_YELLOW A3
#define Cha3LED_GREEN A4
#define Cha4LED_BLUE A5
#define Cha1BUTTON 2
#define Cha2BUTTON 3
#define Cha3BUTTON 4
#define Cha4BUTTON 5
#define OpampSet1 6
#define OpampSet2 7
#define OpampSet3 8
#define OpampSet4 9

bool button_1, button_2, button_3, button_4, previous_1,
     previous_2, previous_3, previous_4;
bool status_1 = 0, status_2 = 0, status_3 = 0, status_4 = 0,
     presta_1 = 0, presta_2 = 0, presta_3 = 0, presta_4 = 0;
unsigned long time[] = {0, 0, 0, 0};
int debounce = 200;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for(int i = 2; i < 6; i++){
    pinMode(i, INPUT);
  }
  pinMode(Cha1LED_RED, OUTPUT);
  pinMode(Cha2LED_YELLOW, OUTPUT);
  pinMode(Cha3LED_GREEN, OUTPUT);
  pinMode(Cha4LED_BLUE, OUTPUT);

  digitalWrite(Cha1LED_RED, LOW);
  digitalWrite(Cha2LED_YELLOW, LOW);
  digitalWrite(Cha3LED_GREEN, LOW);
  digitalWrite(Cha4LED_BLUE, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:'

  //"""""""""Sense""""""""""""
  button_1 = digitalRead(Cha1BUTTON);
  button_2 = digitalRead(Cha2BUTTON);
  button_3 = digitalRead(Cha3BUTTON);
  button_4 = digitalRead(Cha4BUTTON);

  //"""""""""Think""""""""""""
  presta_1 = status_1;
  if(button_1 == 1 && previous_1 == 0 && millis() - time[0] >= debounce){
    if(status_1 == HIGH){
      status_1 = LOW;
    }else if(status_1 == LOW){
      status_1 = HIGH;
    }
    time[0] = millis();
  }
  presta_2 = status_2;
  if(button_2 == 1 && previous_2 == 0 && millis() - time[1] >= debounce){
    if(status_2 == HIGH){
      status_2 = LOW;
    }else if(status_2 == LOW){
      status_2 = HIGH;
    }
    time[1] = millis();
  }
  presta_3 = status_3;
  if(button_3 == 1 && previous_3 == 0 && millis() - time[2] >= debounce){
    if(status_3 == HIGH){
      status_3 = LOW;
    }else if(status_3 == LOW){
      status_3 = HIGH;
    }
    time[2] = millis();
  }
  presta_4 = status_4;
  if(button_4 == 1 && previous_4 == 0 && millis() - time[3] >= debounce){
    if(status_4 == HIGH){
      status_4 = LOW;
    }else if(status_4 == LOW){
      status_4 = HIGH;
    }
    time[3] = millis();
  }
  previous_1 = button_1;
  previous_2 = button_2;
  previous_3 = button_3;
  previous_4 = button_4;

  //"""""""""Act""""""""""""
  if(presta_1 != status_1){
    digitalWrite(Cha1LED_RED, status_1);
    digitalWrite(OpampSet1, status_1);
  }
  if(presta_2 != status_2){
    digitalWrite(Cha2LED_YELLOW, status_2);
    digitalWrite(OpampSet2, status_2);
  }
  if(presta_3 != status_3){
    digitalWrite(Cha3LED_GREEN, status_3);
    digitalWrite(OpampSet3, status_3);
  }
  if(presta_4 != status_4){
    digitalWrite(Cha4LED_BLUE, status_4);
    digitalWrite(OpampSet4, status_4);
  }
}
