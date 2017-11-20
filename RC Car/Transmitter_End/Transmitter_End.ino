#include <SPI.h>
#include <Wire.h>
#include <RF24.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuck = ArduinoNunchuk();
RF24 myRadio(7, 8);
byte address[][6] = {"1Node", "2Node"};
byte nun_address, present = 0, previous = 0, c_button;
unsigned long sent_time, start_waiting_at, end_time, debounce = 50;
unsigned long time[4] = {0, 0, 0, 0};
bool zeroGear;

struct infoBatch{
  int xPosi;
  int yPosi;
  byte motorGear;
} controller;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("*********** This controls the transmit node of the project ********"));
  nunchuck.init();
  myRadio.begin();

  myRadio.setPALevel(RF24_PA_LOW);
  myRadio.setChannel(108);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openReadingPipe(1, address[0]);
  myRadio.openWritingPipe(address[1]);
  Serial.println(F("\n\t*********** Loading Complete ***********"));
  myRadio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(nun_presence()){
    nunchuck.update();
    controller.xPosi = nunchuck.analogX;
    controller.yPosi = nunchuck.analogY;
    c_button = nunchuck.cButton;

    /****The section on directions of the front wheel****/
    /*if(controller.xPosi == 128){
      controller.xPosi = 85; 
    }else{
      controller.xPosi = map(controller.xPosi, 1, 254, 135, 45);
    }
    Serial.println(controller.xPosi);*/
    /*=====The end of the direction section=====*/

    
    /****The section on switching gears****/
    //Press C button for 1 seconds to reset the gear
    if(previous == LOW && c_button == HIGH){
      time[1] = millis();
    }else if(previous == HIGH && c_button == LOW) {
      time[2] = millis();
      if(time[2] - time[1] >= 1000){
        zeroGear = true;
      }
      time[1] = time[2] = millis();
    }else if(previous == HIGH && c_button == HIGH && millis() - time[1] > 200){
      controller.motorGear = 1;
    }
    
    //Nonzero Gear Switching
    if(controller.motorGear == 0 && millis() - time[0] >= debounce && previous == LOW && c_button == HIGH){
      controller.motorGear = 1;
      time[0] = millis();
    }else if(controller.motorGear == 1 && millis() - time[0] >= debounce && previous == LOW && c_button == HIGH){
      controller.motorGear = 2;
      time[0] = millis();
    }else if(controller.motorGear == 2 && millis() - time[0] >= debounce && previous == LOW && c_button == HIGH){
      controller.motorGear = 3;
      time[0] = millis();
    }else if(controller.motorGear != 0 && zeroGear){
      controller.motorGear = 0;
      zeroGear = false;
    }else if(controller.motorGear == 3 && millis() - time[0] >= debounce && previous == LOW && c_button == HIGH){
      controller.motorGear = 1;
      time[0] = millis();
    }
    /*====The end of the gear switching section====*/

    /****The section on transmitting over nRF24L01****/
    myRadio.stopListening();
    sent_time = micros();
  
    //Serial.println(F("Now Sending"));
    if(!myRadio.write(&controller, sizeof(controller) )) {
      //Serial.println(F("Sending Failed"));
    }
  
    start_waiting_at = micros();
    bool timeout = false;
    myRadio.startListening();
  
    while(!myRadio.available()) {
      if(micros() - start_waiting_at > 200000) {
        timeout = true;
        break;
      }
    }
    
    if(!timeout) {
      myRadio.read(&controller, sizeof(controller));
      end_time = micros();
  
      /*Serial.print(F("Round-trip delay "));
      Serial.print(end_time - sent_time);
      Serial.println(F(" microseconds"));*/
    }else{
      //Serial.println(F("Failed, response timed out"));
    }
    /*====The end of the wireless tranmission section====*/

    previous = c_button;

    delay(5);
  }else{
    Serial.println("\nPlease plug in your controller and press RESET on the Arduino");
    delay(10000);
  }
}

/*Check the status of the controller by verifying a device's presence at
Address 82 on the I2C bus*/
boolean nun_presence() {
  Wire.beginTransmission(0x52);
  if(!Wire.endTransmission()) {
    return true;
  }else{
    return false;
  }
}
