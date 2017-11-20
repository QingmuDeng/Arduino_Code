int inPin = 2;
unsigned long previousTime;
int led = 3;
long interval = 2000;

void setup() {
  pinMode(inPin, INPUT);
  for(int i = 3; i < 9; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  unsigned long currentTime = millis();
  int switchStatus = digitalRead(inPin);
  if(currentTime - previousTime > interval) {
    digitalWrite(led, HIGH);
    led++;
    previousTime = currentTime;

    if(led == 9) {
      delay(1500);
      for(int a = 0; a < 5; a++) {
        for(int i = 3; i < 9; i ++) {
          digitalWrite(i, LOW);
        }
        delay(300);
        for(int i = 3; i < 9; i ++) {
          digitalWrite(i, HIGH);
        }
        delay(300);
      }
      //reset timer for the LEDs
      previousTime = currentTime;
      do {
        //check the time in every loop
        currentTime = millis();
        //first scenario
        if(currentTime - previousTime <= 300) {
          for(int i = 3; i < 9; i += 2) {
            digitalWrite(i, LOW);
          }
          for(int i = 4; i < 9; i += 2) {
            digitalWrite(i, HIGH);
          }
        }
        //second scenario
        if(currentTime - previousTime > 300 && currentTime - previousTime <= 600) {
          for(int i = 3; i < 9; i += 2) {
            digitalWrite(i, HIGH);
          }
          for(int i = 4; i < 9; i += 2) {
            digitalWrite(i, LOW);
          }
        }
        //reset once one loop of the pattern finishes
        if(currentTime - previousTime > 600) {
          previousTime = currentTime;
        }
        //check the switch status
        switchStatus = digitalRead(inPin);
      }while(switchStatus == 0);
    }
  }



  if(switchStatus != 0) {
    for(int i = 3; i < 9; i++) {
    digitalWrite(i, LOW);
   }
   led = 3;
   previousTime = currentTime;
  }
  switchStatus = 0;
}

