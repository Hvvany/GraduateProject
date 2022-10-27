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
int before_distance = 400;
int difference = 0;
double avg;

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
  angle = 0;
}

//-------------------------------------------------------------------------------------------------------------------------------

void loop() {
//    if(digitalRead(SIGNAL_PIN) == HIGH) {           // PIR 감지하면
      pinMode(3, OUTPUT);                           // led 작동
      digitalWrite(3, HIGH);
      Serial.println("Person was detected!");
      
      servo.write(angle);
      for(angle; angle < 100; angle=angle + 1){       // 각도 감소
        
//        if(digitalRead(SIGNAL_PIN) == LOW) {        // pir 사람 없으면
//          pinMode(3, OUTPUT);                            // led 불 끄고
//          digitalWrite(3, LOW);
//          break;                                         // 다음 for문 진입
//          }
//        else {                                      // pir 사람 감지 하면
          servo.write(angle); 
          if(TFmini.measure()){                     // 라이다에 값이 들어오면
              distance = TFmini.getDistance();
//              delay(40);
              Serial.print("Angle = ");
              Serial.println(angle);                // 각도 표현

              Serial.print("before_distance : ");          // 거리 표현
              Serial.println(before_distance);

              if(distance < 30 or distance > 400){
                 distance = 600;
              }
              Serial.print("distance : ");          // 거리 표현
              Serial.println(distance);
              Serial.println("cm");
              difference = distance - before_distance;
              Serial.print("difference : ");          // 거리 표현
              Serial.println(difference);

              
              if ( difference > 200){
                before_distance = distance;
                break;
                }
                before_distance = distance; 
              }
              delay(4);
          
//        }
        
      }

      
      servo.write(angle);
      for(angle; angle > 0; angle = angle - 1){       // 각도 감소
        
//        if(digitalRead(SIGNAL_PIN) == LOW) {        // pir 사람 없으면
//          pinMode(3, OUTPUT);                            // led 불 끄고
//          digitalWrite(3, LOW);
//          break;                                         // 다음 for문 진입
//          }
//        else {                                      // pir 사람 감지 하면
          servo.write(angle); 
          if(TFmini.measure()){                     // 라이다에 값이 들어오면
              distance = TFmini.getDistance();
//              delay(40);
              Serial.print("Angle = ");
              Serial.println(angle);                // 각도 표현

              Serial.print("before_distance : ");          // 거리 표현
              Serial.println(before_distance);

              if(distance < 30 or distance > 400){
                 distance = 600;
              }
              Serial.print("distance : ");          // 거리 표현
              Serial.println(distance);
              Serial.println("cm");
              difference = distance - before_distance;
              Serial.print("difference : ");          // 거리 표현
              Serial.println(difference);

              
              if ( difference > 200){
                before_distance = distance;
                break;
                }
                before_distance = distance; 
              }
           delay(4);
          
//        }
        
      }
//    }
//    else{
//      Serial.println("NO PERSON");
//      pinMode(3, OUTPUT);
//      digitalWrite(3, LOW);
//      angle = 0;
//    }
}
