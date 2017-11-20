#include <Servo.h>
Servo newServo;

const byte switchPin = 12;
const byte red = 10;
const byte yellow = 9;
const byte green = 8;
const int Piezo = A0;
int Photoresistor = A1;
byte numKnocked = 0;
boolean locked = false;
int minimumKnock = 15;
int maximumKnock = 100;
int knockValue;
int previous = LOW;
unsigned long Time[3] = {0, 0, 0};
unsigned long printTime = 0;
long debounce = 200;
boolean knockCheck(int value);
int a = 0;
boolean b = false;

void setup() {
  // put your setup code here, to run once:
  newServo.attach(6);
  pinMode(switchPin, INPUT);
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
  newServo.write(0);
  digitalWrite(green, HIGH);
  Serial.println("The box is unlocked");
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = digitalRead(switchPin);

  //the switch
  if(previous == LOW && reading == HIGH && millis() - Time[0] > 300) {
    Photoresistor = A1;
    Time[1] = 0;
    numKnocked = 0;
    b = false;
    if(locked == false) {
      locked = true;
      newServo.write(90);
      digitalWrite(green, LOW);
      digitalWrite(red, HIGH);
      delay(500);
    }
    Time[0] = millis();
    Time[1] = millis();
    Serial.println("Timer 2 starts");
  }

  if(millis() - Time[1] < 3000){
    int photoReading = analogRead(Photoresistor);
    b = resistorReading(photoReading);
  } else if(millis() - Time[1] ==  3000 && b == true){
    Time[2] = millis();
    Serial.println("Timer 3 starts");
  }
  
  if(locked == true) {
      //Serial.println(photoReading);
       //Serial.println(Time[2]);
      if(b == true && millis() - Time[2] <= 5000 && millis() - Time[2] >= 0) {
      //Serial.println(millis() - Time[2]);
      digitalWrite(green, HIGH);
      knockValue = analogRead(Piezo);
      if(numKnocked < 3 && numKnocked >= 0){
        a = numKnocked;
        if(knockCheck(knockValue) == true) {
          numKnocked ++;
        }
        if(a != numKnocked) {
          Serial.print(3 - numKnocked);
          Serial.println(" more to go");
        }
      }
  
      if(numKnocked >= 3) {
        newServo.write(0);
        digitalWrite(red, LOW);
        digitalWrite(green, HIGH);
        Serial.println("The box is unlocked"); 
        locked = false;     
        delay(500);
      }
    }
  }
  previous = reading;
}

boolean knockCheck(int value) {
  if(value >= minimumKnock && value <= maximumKnock) {
    Serial.print("Good Knock Value ");
    Serial.println(value);
    digitalWrite(yellow, HIGH);
    delay(50);
    digitalWrite(yellow, LOW);
    return true;
  } else {
    if(value != 0) {
      Serial.print("Bad Knock Value ");
      Serial.println(value);
    }
    return false;
  }
}

boolean resistorReading(int value) {
  if(value >= 900) {
    return true;
  }else {
    Serial.println(millis() - Time[1]);
    return false;
  }
}

