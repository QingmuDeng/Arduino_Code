#include <NewPing.h>
#include <SPI.h>
#include <Servo.h>
#include <RF24.h>

RF24 receiver(7, 8);

Servo dirServo, sonicServo;
byte address[][6] = {"1Node", "2Node"};
byte turn = 0, sonicAngle;
int absY, maxY, motorSpeedL, motorDif, motorSpeedR, baseSpeed;
const byte echo = A2, trig = A3, ENR = 6, ENL = 5, motorR1 = 4, motorR2 = 3, motorL1 = A0, motorL2 = A1;
NewPing sonar(trig, echo, 200);
float distance;
unsigned long duration, time[2] = {0, 0};

struct infoBatch{
  int xPosi;
  int yPosi;
  byte c_button;
  byte motorGear;
} controller;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("*********** This controls the receiver node of the project ********"));
  receiver.begin();
  dirServo.attach(9);
  sonicServo.attach(10);
  sonicServo.write(45);
  pinMode(echo, INPUT);
  digitalWrite(trig, LOW);
  for(int i = 2; i < 7; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
  pinMode(motorL1, OUTPUT);
  pinMode(motorL2, OUTPUT);
  
  
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
    /*Serial.print(F("Sent "));
    Serial.println(controller._micros);*/
    receiver.startListening();
  }

/*****The beginning of the section on turning the front wheel*****/
  //dirServo.write(controller.xPosi);
  if(controller.xPosi == 128){
      motorDif = 0; 
    }else{
      motorDif = abs(controller.xPosi - 128);
      motorDif = map(motorDif, 0, 127, 0, 50);
    }
/*=====The end of the section on turning the front wheel=====*/

/*****The beginning of the section on two electric motors*****/
  absY = controller.yPosi - 130;
  //Serial.println(absY);
  if(absY > 0){
    forward();
    maxY = 125;
    delay(2);
  }else if(absY < 0){
    reverse();
    maxY = 130;
    absY = abs(absY);
    delay(2);
  }

  if(controller.motorGear == 0){
    baseSpeed = motorSpeedL = 0;
  }else if(controller.motorGear == 1){
    baseSpeed = motorSpeedL = map(absY, 0, maxY, 0, 110);
  }else if(controller.motorGear == 2){
    baseSpeed = motorSpeedL = map(absY, 0, maxY, 0, 200);
  }else if(controller.motorGear == 3){
    baseSpeed = motorSpeedL = map(absY, 0, maxY, 0, 255);
  }
  motorSpeedR = motorSpeedL;
  if(controller.motorGear != 0 && controller.xPosi > 128 && baseSpeed >= 50){
    motorSpeedL -= motorDif;
  }else if(controller.motorGear != 0 && controller.xPosi < 128 && baseSpeed >= 50){
    motorSpeedR -= motorDif;
  }
  enable(motorSpeedR, motorSpeedL);

  Serial.print(motorSpeedR);
  Serial.print("\t\t");
  Serial.println(motorSpeedL);
/*=====The end of the section on two electric motors=====*/

  //Serial.print("Motor Gear ");
  //Serial.println(controller.motorGear);

/******Ultrasonic Sensor Section*******/ 
  if(millis() - time[1] > 150){
    if(Ultrasonic_distance()){
      sonicAngle = sonicServo.read();
      if(sonicServo.read() >= 135 && turn == 0){
        turn = 1;
      }else if(sonicServo.read() <= 45 && turn == 1){
        turn = 0;
      }
  
      if(turn == 0){
        sonicServo.write(sonicServo.read() + 15);
      }else if(turn == 1) {
        sonicServo.write(sonicServo.read() - 15);
      }
      //Serial.println(sonicServo.read());
    }
    time[1] = millis();
  }
  

//Decision-making based on the info from the sensor
/************************************************/
  if(distance <= 20.0 && distance > 3.0){
    //if the obstacle is right in the front, back up a little and
    //turn 180 degrees
    if(sonicAngle <= 100 && sonicAngle >= 80){
      digitalWrite(motorR1, HIGH);
      digitalWrite(motorR2, LOW);
      digitalWrite(motorL1, LOW);
      digitalWrite(motorL2, HIGH);
      /*time[0] = millis();
      while(millis() - time[0] <= 500){
        enable(255, 255);
      }*/
      //dirServo.write(135);
      
      //Set the car to forward
      //reverse();
      time[0] = millis();
      while(millis() - time[0] <= 700){
        enable(255, 255);
      }
    }

    //If the obstacle is to the right of car, turn left
    if(sonicAngle >= 100){
      //dirServo.write(45);
      Serial.println("True?");
      reverse();
      time[0] = millis();
      while(millis() - time[0] <= 200){
        enable(0, 255);
        }
      }

    //If the obstacle is to the left of car, turn right
    if(sonicAngle <= 80){
      dirServo.write(135);
      reverse();
      time[0] = millis();
      while(millis() - time[0] <= 200){
        enable(255, 0);
      }
    }
  }
/*=====The end of the decision making section=====*/
}

boolean Ultrasonic_distance() {
  duration = sonar.ping_median(3);

  distance = (float)duration / 58.31;
  if(distance > 150.0){
    //Serial.println("All clear...");
  }else{
    /*Serial.print(distance);
    Serial.println(" centimeters");*/
  }

  return true;
}

void reverse(){
  digitalWrite(motorR1, HIGH);
  digitalWrite(motorR2, LOW);
  digitalWrite(motorL1, HIGH);
  digitalWrite(motorL2, LOW);
}

void forward(){
  digitalWrite(motorR1, LOW);
  digitalWrite(motorR2, HIGH);
  digitalWrite(motorL1, LOW);
  digitalWrite(motorL2, HIGH);
}

void enable(int R, int L){
  analogWrite(ENR, R);
  analogWrite(ENL, L);
}

