#include <NewPing.h>
#include <SPI.h>
#include <Servo.h>
#include <RF24.h>

#define ECHO A2
#define TRIG A3
#define ENL 6
#define ENR 5
#define motorL1 4
#define motorL2 3
#define motorR1 A0
#define motorR2 A1
#define SONIC 10

RF24 receiver(7, 8);
Servo sonicServo;
NewPing sonar(TRIG, ECHO, 200);
byte address[][6] = {"1Node", "2Node"};
byte turn = 0, sonicAngle;
int absY, maxY, motorSpeedL, motorDif, motorSpeedR, baseSpeed;
float distance;
unsigned long duration, time[2] = {0, 0};
struct infoBatch{
  int xPosi;
  int yPosi;
  byte motorGear;
} controller;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("*********** This controls the receiver node of the project ********"));
  receiver.begin();
  sonicServo.attach(SONIC);
  sonicServo.write(45);
  for(int i = 2; i < 7; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);

  receiver.setPALevel(RF24_PA_LOW);
  receiver.setChannel(108);
  receiver.setDataRate(RF24_250KBPS);
  receiver.openReadingPipe(1, address[1]);
  receiver.openWritingPipe(address[0]);
  Serial.println(F("*********** Loading Complete ***********"));
  receiver.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(receiver.available()){
    while(receiver.available()){
      receiver.read(&controller, sizeof(controller));
    }
    receiver.stopListening();
    receiver.write(&controller, sizeof(controller));
    receiver.startListening();
  }

  /*****The beginning of the section on turning the front wheel*****/
  if(controller.xPosi == 128){
    motorDif = 0;
  }else{
    motorDif = abs(controller.xPosi - 128);
    motorDif = map(motorDif, 0, 127, 0, 50);
  }
  /*=====The end of the section on turning the front wheel=====*/

  /******The beginning of the section on two electric motors******/
  absY = controller.yPosi - 130;
  if(absY > 0){
    forward();
    maxY = 125;
    delay(1);
  }else if(absY < 0){
    reverse();
    maxY = 130;
    absY = abs(absY);
    delay(1);
  }

  if(controller.motorGear == 0){
    baseSpeed = motorSpeedL = 0;
  }else if(controller.motorGear == 1){
    baseSpeed = motorSpeedL = map(absY, 0, maxY, 0, 120);
  }else if(controller.motorGear == 2){
    baseSpeed = motorSpeedL = map(absY, 0, maxY, 0, 200);
  }else if(controller.motorGear == 3){
    baseSpeed = motorSpeedL = map(absY, 0, maxY, 0, 255);
  }
  motorSpeedR = motorSpeedL;
  if(controller.motorGear != 0 && controller.xPosi > 128 && baseSpeed >= 50){
    motorSpeedR -= motorDif;
  }else if(controller.motorGear != 0 && controller.xPosi < 128 && baseSpeed >= 50){
    motorSpeedL -= motorDif;
  }
  enable(motorSpeedL, motorSpeedR);
  /*=====The end of the section on two electric motors=====*/

  /******Ultrasonic Sensor Section*******/ 
  if(millis() - time[1] > 150){
    if(Ultrasonic_distance()){
      sonicAngle = sonicServo.read();
      if(sonicAngle >= 135 && turn == 0){
        turn = 1;
      }else if(sonicAngle <= 45 && turn == 1){
        turn = 0;
      }

      if(turn == 1){
        sonicServo.write(sonicServo.read() - 15);
      }else if(turn == 0){
        sonicServo.write(sonicServo.read() + 15);
      }
    }
    time[1] = millis();
  }

  //Decision-making based on the info from the sensor
  if(distance <= 20.0 && distance >= 3.0){

    if(sonicAngle > 80 && sonicAngle < 100){
      digitalWrite(motorL1, HIGH);
      digitalWrite(motorL2, LOW);
      digitalWrite(motorR1, LOW);
      digitalWrite(motorR2, HIGH);

      time[0] = millis();
      while(millis() - time[0] <= 700){
        enable(255, 255);
      }
    }

    if(sonicAngle > 100){
      reverse();
      time[0] = millis();
      while(millis() - time[0] <= 200){
        enable(0, 255);
      }
    }

    if(sonicAngle < 80){
      reverse();
      time[0] = millis();
      while(millis() - time[0] <= 200){
        enable(255, 0);
      }
    }
  }
}

void forward(){
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
}

void reverse(){
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
}

void enable(int L, int R){
  analogWrite(ENR, L);
  analogWrite(ENL, R);
}

boolean Ultrasonic_distance(){
  duration = sonar.ping_median(3);
  distance = (float)duration / 58.31;
  return true;
}
