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

// 좌표 선언
#include <math.h>
const double pi = 3.1415926;


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
//      Serial.println("Person was detected!");

      servo.write(angle);
      for(angle; angle < 90; angle=angle + 1){       // 각도 감소

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
//              Serial.print("Angle = ");
//              Serial.println(angle);                // 각도 표현
//
//              Serial.print("before_distance : ");          // 거리 표현
//              Serial.println(before_distance);

              if(distance < 20 or distance > 140){
                 distance = 1000;
//              }
//              Serial.print("distance : ");          // 거리 표현
//              Serial.println(distance);
//              Serial.println("cm");
              difference = distance - before_distance;
//              Serial.print("difference : ");          // 거리 표현
//              Serial.println(difference);
//----------------------------------------------------------------------------------------------------------------
              // 좌표 변환
              servo.write(angle);

              ///좌표 변환 및 구역 나누기
              double x = distance * cos(angle * pi / 180);
              double y = distance * sin(angle * pi / 180);
//              Serial.println("\nx");
//              Serial.print(x);
//              Serial.println("\ny");
//              Serial.print(y);
//              Serial.println("\nangle");
//              Serial.print(angle);

              if(x>70&&y>70){                   ///////1번 구역
//                digitalWrite(10, HIGH);
                Serial.println("1번 구역");
                servo.write(31);
              }
              else if(x>70&&y>0&&y<=70){        ///////2번 구역
//                digitalWrite(11, HIGH);
                Serial.println("2번 구역");
                servo.write(angle);
              }
              else if(x>0&&x<=70&&y>70){        ///////3번 구역
//                digitalWrite(12, HIGH);
                Serial.println("3번 구역");
                servo.write(angle);
              }
              else if(x>0&&x<=70&&y>0&&y<=70){   ///////4번 구역
//                digitalWrite(13, HIGH);
                Serial.println("4번 구역");
                servo.write(angle);
              }


//----------------------------------------------------------------------------------------------------------------             
              if ( difference > 100){
                before_distance = distance;
                break;
                }
                before_distance = distance; 
              }
              delay(4);

        }

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
//              Serial.print("Angle = ");
//              Serial.println(angle);                // 각도 표현
//
//              Serial.print("before_distance : ");          // 거리 표현
//              Serial.println(before_distance);

              if(distance < 20 or distance > 140){
                 distance = 1000;
              }
//              Serial.print("distance : ");          // 거리 표현
//              Serial.println(distance);
//              Serial.println("cm");
              difference = distance - before_distance;
//              Serial.print("difference : ");          // 거리 표현
//              Serial.println(difference);
              //----------------------------------------------------------------------------------------------------------------
              // 좌표 변환
              servo.write(angle);

              ///좌표 변환 및 구역 나누기
              double x = distance * cos(angle * pi / 180);
              double y = distance * sin(angle * pi / 180);
//              Serial.println("\nx");
//              Serial.print(x);
//              Serial.println("\ny");
//              Serial.print(y);
//              Serial.println("\nangle");
//              Serial.println(angle);

              if(x>70&&y>70){                   ///////1번 구역
//                digitalWrite(10, HIGH);
                Serial.println("\n1번 구역");

              }
              else if(x>70&&y>0&&y<=70){        ///////2번 구역
//                digitalWrite(11, HIGH);
                Serial.println("\n2번 구역");

              }
              else if(x>0&&x<=70&&y>70){        ///////3번 구역
//                digitalWrite(12, HIGH);
                Serial.println("\n3번 구역");

              }
              else if(x>0&&x<=70&&y>0&&y<=70){   ///////4번 구역
//                digitalWrite(13, HIGH);
                Serial.println("\n4번 구역");

              }


//----------------------------------------------------------------------------------------------------------------             


              if ( difference > 100){
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
