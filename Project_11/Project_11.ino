#include <LiquidCrystal.h>
#include <string.h>

LiquidCrystal lcd(2, 3, 6, 7, 8, 9);
int const SwitchPin = 10;
int number;
byte reading;
byte previous = LOW;
long debounce = 200;
unsigned long Time = 0;
long Interval = 500;
long previousTime = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  pinMode(SwitchPin, INPUT);

  lcd.setCursor(0, 0);
  lcd.print("Famous Star");
  lcd.setCursor(0, 1);
  lcd.print("Wars Quotes!");
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = digitalRead(SwitchPin);
  if(previous == LOW && reading == HIGH && millis() - Time > debounce) {
    randomSeed(analogRead(A0));
    number = random(6)+1;
    lcd.clear();
    Time = millis();
  }
  previous = reading;
  lcd.setCursor(0, 0);
  lcd.noAutoscroll();
  switch(number) {
      case 1:
      if(millis() - previousTime > 250) {
      lcd.setCursor(15, 0);
      lcd.print("May the force be with you!");
      lcd.scrollDisplayLeft();
      //delay(500);
      previousTime = millis();
      }
      //lcd.print("May the force be with you");
      //lcd.setCursor(0, 1);
      //lcd.print("be with you!");
      break;

      case 2:
      lcd.print("Do or do not.");
      lcd.setCursor(0, 1);
      lcd.print("There is no try.");
      break;

      case 3:
      lcd.print("It's a trap!");
      lcd.setCursor(0, 1);
      lcd.print("- Admiral Ackbar");
      break;

      case 4:
      lcd.print("Light Darkness");
      lcd.setCursor(0, 1);
      lcd.print("A balance.");
      break;

      case 5:
      lcd.print("I am your");
      lcd.setCursor(0, 1);
      lcd.print("father!");
      break;

      case 6:
      lcd.print("- I love you.");
      lcd.setCursor(0, 1);
      lcd.print("- I know.");
      break;
    }
}

