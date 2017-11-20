const int sensorPin = A0;
int analogInput;
float voltage, temp, bselnTemp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //pinMode definition
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(6, INPUT);
  for(int i = 2; i < 6; i++) {
    pinMode(i,OUTPUT);
    digitalWrite(i, LOW);
  };
  
  //Signal the start of the program
  for(int i = 0; i < 4; i++) {
    digitalWrite(5, HIGH);
    delay(100);
    digitalWrite(5, LOW);
    delay(100);
  };



  //Establish the baseline temperature
  for(int i = 0; i < 10; i++) {
    analogInput = analogRead(A0);
    voltage = (analogInput/1024.0) * 5.0;
    temp = (voltage - 0.5) * 100;
    bselnTemp += temp;
    delay(1);
  };
  bselnTemp = bselnTemp/10;
  Serial.print("\n\nThe baseline temperature: ");
  Serial.println(bselnTemp);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonStatus = digitalRead(6);
  digitalWrite(LED_BUILTIN, 0);
  if(buttonStatus == 1) {
    /*for(int i = 3; i < 6; i++) {
      digitalWrite(i, LOW);
     };*/
    analogInput = analogRead(A0);
    voltage = (analogInput/1024.0) * 5.0;
    temp = (voltage - 0.5) * 100;
    //bselnTemp = temp;
    Serial.print("\nThe  temperature: ");
    Serial.println(temp);
    delay(1);
    digitalWrite(2, HIGH);
    delay(100);
    digitalWrite(2, LOW);
    delay(100);
  }
  analogInput = analogRead(A0);
  /*Serial.print("Sensor Value: ");
  Serial.print(analogInput);*/
    
  voltage = (analogInput/1024.0) * 5.0;
  /*Serial.print(", Voltage: ");
  Serial.print(voltage);*/
  
  temp = (voltage - 0.5) * 100;
  /*Serial.print(", Temperature: ");
  Serial.println(temp);*/
  
  if(temp < bselnTemp) {
    for(int i = 3; i < 6; i++) {
      digitalWrite(i, LOW);
   };
  }else if(temp >= bselnTemp+2 && temp < bselnTemp+4) {
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  } else if(temp >= bselnTemp+4 && temp < bselnTemp+6) {
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
  } else if(temp >= bselnTemp+6) {
    for(int i = 3; i < 6; i++) {
      digitalWrite(i, HIGH);
     };
    }
    delay(100);
}
