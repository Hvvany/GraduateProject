//라이다 선언
#include <DFRobot_TFmini.h>
SoftwareSerial mySerial(8, 7); // RX, TX
DFRobot_TFmini  TFmini;
uint16_t distance,strength;

// 서보 선언
#include <Servo.h>
Servo servo;
Servo servo2;

// PIR 선언
#define SIGNAL_PIN 10

// 좌표 선언
#include <math.h>
const double pi = 3.1415926;

const int trigPinM = 7;
const int echoPinM = 8;

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

int angle = 0;
int Shot = 200;  // 서보모터 초기값, 거리 경계값

void setup() {

  servo.attach(9);
  servo.write(45);
  
  // 라이다 셋업
  TFmini.begin(mySerial);
  // 라이트 셋업
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  // PIR 셋업
  pinMode(SIGNAL_PIN, INPUT);
  angle = 0;

  pinMode(trigPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(trigPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  
}

void loop() {
   
   distanceM = TFmini.getDistance();    //중앙의 초음파 시간으로 물체의 위치 계산

   digitalWrite(trigPinR, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPinR, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinR, LOW);
   durationR = pulseIn(echoPinR, HIGH);
   distanceR = durationR * 0.034/2;    //오른쪽의 초음파 시간으로 물체의 위치 계산
   if (distanceR>200) {
    distanceR=200;
   }

   digitalWrite(trigPinL, LOW);
   delayMicroseconds(2);
   digitalWrite(trigPinL, HIGH);
   delayMicroseconds(10);
   digitalWrite(trigPinL, LOW);
   durationL = pulseIn(echoPinL, HIGH);
   distanceL = durationL*0.034/2;    //왼쪽의 초음파 시간으로 물체의 위치 계산
   if (distanceL>200) {
    distanceL=200;
   }

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
servo2.write(angle/2);


    ///좌표 변환 및 구역 나누기
    double x = distanceM * cos(angle * pi / 180);
    double y = distanceM * sin(angle * pi / 180);
    Serial.println("\nx");
    Serial.print(x);
    Serial.println("\ny");
    Serial.print(y);
    Serial.println("\nangle");
    Serial.print(angle);
    
    if(x>70&&y>70){         ///////1번 구역
      digitalWrite(10, HIGH);
      Serial.println("1번 구역");
      
    }
    else if(x>70&&y>0&&y<=70){      ///////2번 구역
      digitalWrite(11, HIGH);
      Serial.println("2번 구역");
      
    }
    else if(x>0&&x<=70&&y>70){      ///////3번 구역
      digitalWrite(12, HIGH);
      Serial.println("3번 구역");
      
    }
    else if(x>0&&x<=70&&y>0&&y<=70){        ///////4번 구역
      digitalWrite(13, HIGH);
      Serial.println("4번 구역");
      
    }
}
