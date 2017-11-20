#include "SevSeg.h"
int a, b;
unsigned long Time;
int reading, interval;

void setup() {
  // put your setup code here, to run once:
  for(int i = 2; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = analogRead(A5);
  interval = map(reading, 0, 1023, 100, 1000);
  
  if(millis() - Time > interval) {
    a++; 
    b++; 
    if(b == 10){
      b = 0;
    }
    if(a == 100) {
      a = 0;
    }
    Time = millis();
  }
  //Display the numbers on the Ones
  if(b == 1){
    writeOne(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 2) {
    writeTwo(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 3) {
    writeThree(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 4) {
    writeFour(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 5) {
    writeFive(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 6) {
    writeSix(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 7) {
    writeSeven(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 8) {
    writeEight(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 9) {
    writeNine(5, 6, 7, 8, 12, 11, 10, 9);
  }else if(b == 0) {
    writeZero(5, 6, 7, 8, 12, 11, 10, 9);
  }

  //Display the numbers on the Tens
  if(a >= 10 && a < 20){
    writeOne(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 20 && a < 30) {
    writeTwo(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 30 && a < 40) {
    writeThree(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 40 && a < 50) {
    writeFour(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 50 && a < 60) {
    writeFive(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 60 && a < 70) {
    writeSix(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 70 && a < 80) {
    writeSeven(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 80 && a < 90) {
    writeEight(2, A4, 3, 4, A0, A1, A2, A3);
  }else if(a >= 90 && a < 100) {
    writeNine(2, A4, 3, 4, A0, A1, A2, A3);
  }else{
    clearDisplay(2, A4, 3, 4, A0, A1, A2, A3);
  }
}
