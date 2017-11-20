#include <SPI.h>
#include <RF24.h>

RF24 myRadio(7, 8);
bool radioNumber = 1;
bool role = 0;
byte address[][6] = {"1Node", "2Node"};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println(F("RF24/examples/GettingStarted"));
  Serial.println(F("*** PRESS 'T' to begin transmitting to the other node"));

  myRadio.begin();
  myRadio.setPALevel(RF24_PA_LOW);

  if(radioNumber){
    myRadio.openWritingPipe(address[0]);
    myRadio.openReadingPipe(1, address[1]);
  }else{
    myRadio.openWritingPipe(address[1]);
    myRadio.openReadingPipe(1, address[0]);
  }

  myRadio.startListening();
  
}

void loop() {
  // put your main code here, to run repeatedly:

  if(role == 1) {
    myRadio.stopListening();

    Serial.println(F("Now Sending..."));
    unsigned long start_time = micros();
    if(! myRadio.write(&start_time, sizeof(unsigned long) )){
      Serial.println(F("Sending failed. "));
    }

    myRadio.startListening();
    unsigned long start_waiting = micros();
    boolean timedout = false;
    while(!myRadio.available()){
      if(micros() - start_waiting > 200000){
        timedout = true;
        break;
      }
    }

    if(timedout) {
      Serial.println(F("Failed, response timed out. "));
    }else{
      unsigned long got_time;
      myRadio.read(&got_time, sizeof(unsigned long) );
      unsigned long end_time = micros();

      Serial.print(F("Sent Message "));
      Serial.print(start_time);
      Serial.print(F(", Got response "));
      Serial.print(got_time);
      Serial.print(F(", Delay time "));
      Serial.print(end_time - start_time);
      Serial.println(F(" microseconds"));
    }

    delay(1000);
  }

  if(role == 0){
    if(myRadio.available()){
      unsigned long got_time;
      while(myRadio.available()){
        myRadio.read(&got_time, sizeof(unsigned long));
      }

      myRadio.stopListening();
      myRadio.write(&got_time, sizeof(unsigned long));
      Serial.print(F("Sent response "));
      Serial.println(got_time);
      myRadio.startListening();
    }
  }


  if(Serial.available()) {
    char c = toupper(Serial.read());
    if(c == 'T' && role == 0) {
      role = 1;
      Serial.println(F("********* Transmit Mode **********"));
    }else if(c == 'R' && role == 1) {
      role = 0;
      Serial.println(F("********* Receiver Mode **********"));
      myRadio.startListening();
    }
    
  }
}



