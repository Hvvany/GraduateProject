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

// PIR 선언
#define SIGNAL_PIN 10


//-------------------------------------------------------------------------------------------------------------------------------
void setup() {
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

void loop() {
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
      
//    if(digitalRead(SIGNAL_PIN) == HIGH) {           // PIR 감지하면
      pinMode(3, OUTPUT);                           // led 작동
      digitalWrite(3, HIGH);
//      Serial.println("Person was detected!");

      servo.write(angle);
      for(angle; angle < 100; angle=angle + 1){       // 각도 감소
        repeat = false;

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

              if(distance < 30 or distance > 250){
                 distance = 600;
              }
//              Serial.print("distance : ");          // 거리 표현
//              Serial.println(distance);
//              Serial.println("cm");
              difference = distance - before_distance;
//              Serial.print("difference : ");          // 거리 표현
//              Serial.println(difference);


              if ( difference > 100){
//                angle_1 = angle;
                if(angle_1!=-100){
                  angle_3 = angle;
                }
                else{
                  angle_1 = angle;
                }
                repeat = true;
                before_distance = distance;
//                now_angle = (angle + before_angle)/4;
//                Serial.print("now_angle");
//                Serial.println(now_angle);
//                if (average_cnt < 5){
//                  average[cnt] = now_angle;
//                }
//                else{
//                  int s = 0;
//                  for (int i=0; i< 5; i++)
//                  {
//                      s += average[i];
//                      Serial.println(average[i]);
//                  }
//                  servo2.write(s/5);
//                  average_cnt = 0;
//                }
//                average_cnt += 1;
//                before_angle = angle;
                break;
                }
                before_distance = distance;
              }
              delay(4);

//        }
        
      }
      if(repeat==false){
        if(angle_1!=-100){
          angle_3 = 100;
        }
        else{
          angle_1 = 100;
        }
      }
//      if (repeat==true){
//        
//        repeat = true;
//        before_distance = distance;
//        now_angle = (angle + before_angle)/4;
//        Serial.print("now_angle");
//        Serial.println(now_angle);
//        if (average_cnt < 5){
//          average[cnt] = now_angle;
//        }
//        else{
//        int s = 0;
//        for (int i=0; i< 5; i++)
//        {
//            s += average[i];
//            Serial.println(average[i]);
//        }
//        servo2.write(s/5);
//        average_cnt = 0;
//        }
//        average_cnt += 1;
//        before_angle = angle;
//      }
      


      servo.write(angle);
      for(angle; angle > 0; angle = angle - 1){       // 각도 감소
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
//              delay(40);
//              Serial.print("Angle = ");
//              Serial.println(angle);                // 각도 표현

//              Serial.print("before_distance : ");          // 거리 표현
//              Serial.println(before_distance);

              if(distance < 30 or distance > 250){
                 distance = 600;
              }
//              Serial.print("distance : ");          // 거리 표현
//              Serial.println(distance);
//              Serial.println("cm");
              difference = distance - before_distance;
//              Serial.print("difference : ");          // 거리 표현
//              Serial.println(difference);


              if ( difference > 100){
                repeat=true;
                before_distance = distance;
                if(angle_2!=-100){
                  angle_4 = angle;
                }
                else{
                  angle_2 = angle;
                }
//                now_angle = (angle + before_angle)/4;
//                if (average_cnt < 5){
//                  average[cnt] = now_angle;
//                }
//                else{
//                int s = 0;
//                  for (int i=0; i< 5; i++)
//                  {
//                      s += average[i];
//                      Serial.println(average[i]);
//                  }
//                  servo2.write(s/5);
//                average_cnt = 0;
//                }
//                average_cnt += 1;
//                before_angle = angle;
                break;
                }
                before_distance = distance;
              }
           delay(4);

//        }
      }
      if(repeat==false){
          if(angle_2!=-100){
            angle_4 = 0;
          }
          else{
            angle_2 = 0;
          }
          }
//      if (repeat==true){
//        
//        repeat = true;
//        before_distance = distance;
//        now_angle = (angle + before_angle)/4;
//        Serial.print("now_angle");
//        Serial.println(now_angle);
//        if (average_cnt < 5){
//          average[cnt] = now_angle;
//        }
//        else{
//        int s = 0;
//        for (int i=0; i< 5; i++)
//        {
//            s += average[i];
//            Serial.println(average[i]);
//        }
//        servo2.write(s/5);
//        average_cnt = 0;
//        }
//        average_cnt += 1;
//        before_angle = angle;
//      }
      
       
//      if(angle<=0){
//        now_angle = (angle + before_angle)/4;
//        servo2.write(now_angle);
//        before_angle = angle;
//      }#--------------------------------------------------------------------
//    }
//    else{
//      Serial.println("NO PERSON");
//      pinMode(3, OUTPUT);
//      digitalWrite(3, LOW);
//      angle = 0;
//    }
}
