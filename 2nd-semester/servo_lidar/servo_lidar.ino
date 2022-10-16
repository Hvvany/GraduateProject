//라이다 선언
#include <DFRobot_TFmini.h>
SoftwareSerial mySerial(8, 7); // RX, TX
DFRobot_TFmini  TFmini;
uint16_t distance,strength;

// 서보 선언
#include <Servo.h>
Servo servo;
int servoPin = 9;
int angle = 0;
int cnt = 0;

// PIR 선언
#define SIGNAL_PIN 10


//-------------------------------------------------------------------------------------------------------------------------------
void setup() {
  // 서보 셋업
  servo.attach(servoPin);
  servo.write(angle);
  // 라이다 셋업
  Serial.begin(115200);
  TFmini.begin(mySerial);
  // 라이트 셋업
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  // PIR 셋업
  pinMode(SIGNAL_PIN, INPUT);
}

//-------------------------------------------------------------------------------------------------------------------------------

void loop() {
    if(digitalRead(SIGNAL_PIN) == HIGH) {
      Serial.println("Person was detected!");
      servo.write(angle);
      for(angle = 0; angle < 100; angle=angle+10){
        if(digitalRead(SIGNAL_PIN) == LOW) {
          break;
          }
        else {
          servo.write(angle);
          if(TFmini.measure()){                      //Measure Distance and get signal strength
              Serial.print("Angle = ");
              Serial.println(angle);
              distance = TFmini.getDistance();       //Get distance data
              strength = TFmini.getStrength();       //Get signal strength data
              Serial.print("Distance = ");
              Serial.print(distance);
              Serial.println("cm");
              delay(400);
          }
          else{
            delay(400);
          }
        }
      }
      for(angle = 100; angle > 0; angle=angle-10){
        if(digitalRead(SIGNAL_PIN) == LOW) {
          break;
          }
        else {
          servo.write(angle);
          if(TFmini.measure()){                      //Measure Distance and get signal strength
              Serial.print("Angle = ");
              Serial.println(angle);
              distance = TFmini.getDistance();       //Get distance data
              strength = TFmini.getStrength();       //Get signal strength data
              Serial.print("Distance = ");
              Serial.print(distance);
              Serial.println("cm");
              delay(400);
          }
          else{
            delay(400);
          }
        }
      }
    }
    else{
    Serial.println("NO PERSON");
    }
}
