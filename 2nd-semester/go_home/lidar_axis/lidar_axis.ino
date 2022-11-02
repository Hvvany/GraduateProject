#include <SoftwareSerial.h>

// 블루투스 선언
int blueTx=2;   //Tx (보내는핀 설정)at
int blueRx=3;   //Rx (받는핀 설정)
int cnt_2=0;
SoftwareSerial btSerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언

// 라이다 선언
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
//  Serial.begin(115200);
  TFmini.begin(mySerial);
  // 라이트 셋업
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  // PIR 셋업
  pinMode(SIGNAL_PIN, INPUT);
  angle = 0;
  // 블루투스
  Serial.begin(9600);                          // 시리얼 통신 선언 (보드레이트 9600)
  btSerial.begin(9600);                     // HC-06 모듈 통신 선언 (보드레이트 9600)
}

//-------------------------------------------------------------------------------------------------------------------------------

void loop() {
//    if(digitalRead(SIGNAL_PIN) == HIGH) {           // PIR 감지하면
      pinMode(4, OUTPUT);                             // led 작동
      digitalWrite(4, HIGH);
      Serial.println("Person was detected!");
      servo.write(angle);
      for(angle; angle < 100; angle=angle + 1){       // 각도 감소
        
//        if(digitalRead(SIGNAL_PIN) == LOW) {        // pir 사람 없으면
//          pinMode(4, OUTPUT);                            // led 불 끄고
//          digitalWrite(4, LOW);
//          break;                                         // 다음 for문 진입
//          }
//        else {                                      // pir 사람 감지 하면
          servo.write(angle); 
          if(TFmini.measure()){                     // 라이다에 값이 들어오면
              distance = TFmini.getDistance();
              btSerial.print(distance);
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
//----------------------------------------------------------------------------------------------------------------
              // 좌표 변환
              servo.write(angle);
              
              ///좌표 변환 및 구역 나누기
              double x = distance * cos(angle * pi / 180);
              double y = distance * sin(angle * pi / 180);
              Serial.println("\nx");
              Serial.print(x);
              Serial.println("\ny");
              Serial.print(y);
              Serial.println("\nangle");
              Serial.print(angle);

              
              if(x>70&&y>70){                   ///////1번 구역
//                digitalWrite(10, HIGH);
                if(cnt_2 > 10){
                btSerial.println("1번 구역");
                cnt_2=0;
                }
              }
              else if(x>70&&y>0&&y<=70){        ///////2번 구역
//                digitalWrite(11, HIGH);
                
                if(cnt_2 > 10){
                btSerial.println("2번 구역");
                cnt_2=0;
                }
                
              }
              else if(x>0&&x<=70&&y>70){        ///////3번 구역
//                digitalWrite(12, HIGH);
                
                if(cnt_2 > 10){
                btSerial.println("3번 구역");
                cnt_2=0;
                }
                
              }
              else if(x>0&&x<=70&&y>0&&y<=70){   ///////4번 구역
//                digitalWrite(13, HIGH);
                
                if(cnt_2 > 10){
                btSerial.println("4번 구역");
                cnt_2=0;
                }
                
              }


//----------------------------------------------------------------------------------------------------------------             
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
//          pinMode(4, OUTPUT);                            // led 불 끄고
//          digitalWrite(4, LOW);
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
              //----------------------------------------------------------------------------------------------------------------
              // 좌표 변환
              servo.write(angle);
              
              ///좌표 변환 및 구역 나누기
              double x = distance * cos(angle * pi / 180);
              double y = distance * sin(angle * pi / 180);
              Serial.println("\nx");
              Serial.print(x);
              Serial.println("\ny");
              Serial.print(y);
              Serial.println("\nangle");
              Serial.print(angle);
              
              if(x>70&&y>70){                   ///////1번 구역
//                digitalWrite(10, HIGH);
                
                if(cnt_2 > 10){
                btSerial.println("\n1번 구역");
                cnt_2=0;
                }
                
              }
              else if(x>70&&y>0&&y<=70){        ///////2번 구역
//                digitalWrite(11, HIGH);
                
                if(cnt > 10){
                btSerial.println("\n2번 구역");
                cnt_2=0;
                }
                
              }
              else if(x>0&&x<=70&&y>70){        ///////3번 구역
//                digitalWrite(12, HIGH);
                
                if(cnt_2 > 10){
                btSerial.println("\n3번 구역");
                cnt_2=0;
                }
                
              }
              else if(x>0&&x<=70&&y>0&&y<=70){   ///////4번 구역
//                digitalWrite(13, HIGH);
                
                if(cnt_2 > 10){
                btSerial.println("\n4번 구역");
                cnt_2=0;
                }
                
              }


//----------------------------------------------------------------------------------------------------------------             

              
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
//      pinMode(4, OUTPUT);
//      digitalWrite(4, LOW);
//      angle = 0;
//    }
    
    if (btSerial.available()) {       
    Serial.write(btSerial.read());  //블루투스측 내용을 시리얼모니터에 출력
    }
    if (Serial.available()) {         
    btSerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
    }
}
