
//----------------------------------------------------------------------------------------------------------------------------
#include "Queue.h"

Queue<int> queue = Queue<int>(); // Queue of max 256 int
//라이다 선언
#include <DFRobot_TFmini.h>
SoftwareSerial mySerial(8, 7); // RX, TX
DFRobot_TFmini  TFmini;
uint16_t distance,strength;

// 서보 선언
#include <Servo.h>
Servo servo;
Servo servo2;
int servoPin = 9;
int servoPin2 = 11;
int angle = 0;
int before_angle = 0;
float now_angle = 0;
int cnt = 0;
int before_distance = 400;
int difference = 0;

int angle_1 = 0;
int angle_2 = 0;
int angle_3 = 0;
int angle_4 = 0;
bool repeat=false;

// PIR 선언
#define SIGNAL_PIN 10

const int trigPinR = 12;
const int echoPinR = 13;

const int trigPinL = 4;
const int echoPinL = 5;

long durationM;
int distanceM;
long durationR;
int distanceR;
long durationL;
int distanceL;
bool pass = false;
int Shot = 200;  // 서보모터 초기값, 거리 경계값
int near_cnt = 0;   // 근거리 모드 최소 유지 시간 위해 설정

//-------------------------------------------------------------------------------------------------------------------------------
void setup() {
  
  servo.attach(9);
  servo.write(45);

  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);

  
  // 서보 셋업
  servo.attach(servoPin);
  servo.write(angle);
  servo2.attach(servoPin2);
  servo2.write(angle);
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
void loop(){
  pass=false;
while(distanceM >= 150) {
  distanceM = 200;
  Serial.println("원거리 모드");
      if(angle_1!=-100 && angle_2!=-100 && angle_3!=-100 && angle_4!=-100){
      now_angle = (angle_1 + angle_2 + angle_3 + angle_4)/8;
      servo2.write(now_angle);
        angle_1 = -100;
        angle_2 = -100;
        angle_3 = -100;
        angle_4 = -100;
        Serial.println("------------------------------------------------------------------------");
        Serial.println(now_angle);
      }
//      Serial.println("111");
      
//    if(digitalRead(SIGNAL_PIN) == HIGH) {           // PIR 감지하면
      pinMode(3, OUTPUT);                           // led 작동
      digitalWrite(3, HIGH);
//      Serial.println("Person was detected!");

      servo.write(angle);
      for(angle; angle < 100; angle=angle + 1){       // 각도 감소
        if(pass){
          Serial.println("pass");
          Serial.println(pass);
          break;
        }
        repeat = false;
                                                     // pir 사람 감지 하면
          servo.write(angle);
          if(TFmini.measure()){                     // 라이다에 값이 들어오면
//              Serial.println("222");
              distance = TFmini.getDistance();
              if(distance < 30 or distance > 250){
//                Serial.println("333");
                 distance = 600;
              }
              difference = distance - before_distance;


              if ( difference > 100){
//                Serial.println("444");
                
                if ( before_distance < 150){
//                  Serial.println("555");
                  pass=true;
                  break;
                }
                if(angle_1!=-100){
                  angle_3 = angle;
                }
                else{
                  angle_1 = angle;
                }
                repeat = true;
                before_distance = distance;
                break;
                }
                before_distance = distance;
              }
              delay(4);
              //}
      }
      if (pass){
        break;
      }

      if(repeat==false){
        if(angle_1!=-100){
          angle_3 = 100;
        }
        else{
          angle_1 = 100;
        }
      }

//-------------------------------------------------------------------------------------------------------------------      


      servo.write(angle);
      for(angle; angle > 0; angle = angle - 1){       // 각도 감소
        if(pass){
          break;
        }
        repeat=false;
        
        

//        if(digitalRead(SIGNAL_PIN) == LOW) {        // pir 사람 없으면
//          pinMode(3, OUTPUT);                            // led 불 끄고
//          digitalWrite(3, LOW);
//          break;                                         // 다음 for문 진입
//          }
//        else {                                      // pir 사람 감지 하면
          servo.write(angle);
          if(TFmini.measure()){                     // 라이다에 값이 들어오면
              distance = TFmini.getDistance();

              if(distance < 30 or distance > 250){
                 distance = 600;
              }
              difference = distance - before_distance;



              if ( difference > 100){
                if ( before_distance < 150){
                  pass=true;
                  break;
                }
                repeat=true;
                before_distance = distance;
                if(angle_2!=-100){
                  angle_4 = angle;
                }
                else{
                  angle_2 = angle;
                }
                break;
                }
                before_distance = distance;
              }
           delay(4);
           //}
      }

      if (pass){
        break;
      }


      if(repeat==false){
          if(angle_2!=-100){
            angle_4 = 0;
          }
          else{
            angle_2 = 0;
          }
          }
      
}



//---------------------------------------------------------------------------------------
near_cnt=0;
while(distanceM < 150 || distanceL < 150 || distanceR < 150 || near_cnt < 20)  {
   Serial.println("근거리 모드");
   Serial.println("near_cnt");
   Serial.println(near_cnt);
   near_cnt += 1;
   if(TFmini.measure()){ 
   distanceM = TFmini.getDistance();    //중앙의 초음파 시간으로 물체의 위치 계산
   }
   
   digitalWrite(trigPinR, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPinR, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinR, LOW);
   durationR = pulseIn(echoPinR, HIGH);
   distanceR = durationR * 0.034/2;    //오른쪽의 초음파 시간으로 물체의 위치 계산

   digitalWrite(trigPinL, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPinL, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinL, LOW);
   durationL = pulseIn(echoPinL, HIGH);
   distanceL = durationL*0.034/2;    //왼쪽의 초음파 시간으로 물체의 위치 계산

   Serial.print("Distance R: ");
   Serial.print(distanceR);
   Serial.println("cm");
   Serial.print("Distance M: ");
   Serial.print(distanceM);
   Serial.println("cm");
   Serial.print("Distance L: ");
   Serial.print(distanceL);
   Serial.println("cm");      //각각의 거리를 시리얼 모니터에 출력

   if(distanceL > Shot && distanceM > Shot && distanceR < Shot){
      angle = angle - 40;     //오른쪽에만 사람이 인식 될 때, 오른쪽으로 방향을 10만큼 수정
      if(angle<2){
        angle = 5;     // 만약 1보다 작을경우 하한치를 10으로 조정
      }
      }
   else if(distanceL > Shot && distanceM < Shot && distanceR < Shot){
        angle = angle - 10;      // 오른쪽과 중앙에서 장애물이 인식 될 때, 오른쪽으로 방향을 5만큼 수정
        if(angle<2){
          angle = 10;
        }
   }
   else if(distanceL < Shot && distanceM > Shot && distanceR > Shot){
    angle = angle + 40;
    if(angle>90){
      angle = 90;
    }
   }
   else if(distanceL < Shot && distanceM < Shot && distanceR > Shot){
    angle = angle + 10;
    if(angle>90){
      angle = 90;
    }
    
}

  servo.write(angle);
  servo2.write(angle/4);

}
before_distance = 150;
}
