//서보 변수 정의
#include <Servo.h>
#include <math.h>
int servoPin = 9;
int angle = 0;
Servo servo;

//Main 초음파 변수 정의
#define  Measure  1     // Mode select
int mainTRIG = 2;       // PWM trigger pin
int mainECHO = 3;       // PWM Output 0-25000US,Every 50US represent 1cm
/*
int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store the value coming from the sensor
*/

//Sub1 초음파 변수 정의
#define sub1_TRIG 5     // TRIG 핀 설정 (초음파 보내는 핀)
#define sub1_ECHO 6     // ECHO 핀 설정 (초음파 받는 핀)

//Sub2 초음파 변수 정의
#define sub2_TRIG 7     // TRIG 핀 설정 (초음파 보내는 핀)
#define sub2_ECHO 8     // ECHO 핀 설정 (초음파 받는 핀)

//pir 변수 정의
#define SIGNAL_PIN 4

//전역변수 선언
unsigned int main_distance= 0;
long sub1_duration, sub1_distance;
long sub2_duration, sub2_distance;
const double pi = 3.1415926;
float far;
unsigned long LowLevelTime = pulseIn(mainECHO, LOW);








void setup() {
  //Main 초음파 Serial initialization
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(mainTRIG,OUTPUT);                  // A low pull on pin COMP/TRIG
  digitalWrite(mainTRIG,HIGH);               // Set to HIGH
  pinMode(mainECHO, INPUT);                  // Sending Enable PWM mode command

  //sub1 초음파 initialization
  pinMode(sub1_TRIG, OUTPUT);
  pinMode(sub1_ECHO, INPUT);
  
  digitalWrite(sub1_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(sub1_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(sub1_TRIG, LOW);


  //sub2 초음파 initialization
  pinMode(sub2_TRIG, OUTPUT);
  pinMode(sub2_ECHO, INPUT);
  
  digitalWrite(sub2_TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(sub2_TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(sub2_TRIG, LOW);


  //서보
  servo.attach(servoPin);
  servo.write(angle);


  //pir
  pinMode(SIGNAL_PIN, INPUT);


  //초기설정 완료 문구
  Serial.println("센서초기설정 완료");
  }


void High_Speed_Sensing_Mode(){

    while(main_distance<=250||sub1_distance<=250||sub2_distance<=250){
      if(sub1_distance<=250&&sub2_distance>250){       //왼쪽 보조 초음파 동작
        angle = angle + 15;
        Main_Distance_Mode();
        Sub1_Distance_Mode();
        Sub2_Distance_Mode();
      }
      if(sub2_distance<=250&&sub1_distance>250){       //오른쪽 보조 초음파 동작
        angle = angle - 15;
        Main_Distance_Mode();
        Sub1_Distance_Mode();
        Sub2_Distance_Mode();
      }
      if(sub1_distance<=250&&sub2_distance<=250){      //왼쪽, 오른쪽 모두 센싱시 왼쪽으로 돌리기 동작
        angle = angle + 15;
        Main_Distance_Mode();
        Sub1_Distance_Mode();
        Sub2_Distance_Mode();
      }
    }
}












    

//  < 참조 함수 정의 > 
void Main_Distance_Mode()                             // main_distance 값 구하기 함수 (cm 단위)
{
  digitalWrite(mainTRIG, LOW);
  digitalWrite(mainTRIG, HIGH);                       // reading Pin PWM will output pulses 
  if(Measure){
    LowLevelTime = pulseIn(mainECHO, LOW);
    
    if(LowLevelTime>=45000){                          // the reading is invalid.
      Serial.print("범위에 대상이 없습니다.\n");
    }
    
    else{
    main_distance = LowLevelTime /50;                 // every 50us low level stands for 1cm
    }  
  }
  else {
    
    /*sensorValue = analogRead(sensorPin);
    if(sensorValue<=10)                               // the reading is invalid.
    {
     Serial.print("Invalid");
    }
    else {
    sensorValue = sensorValue*0.718;     
    PrintingMode();*/
  }
}



void Far_Area_Detecting_Mode()
{
    unsigned long LowLevelTime = pulseIn(mainECHO, LOW);
      while(LowLevelTime>=45000){
      float y1=0.25;
      float i=0;
        if(0<=i<5){                                  //y값이 0.5씩 증가하며 측정
          angle = (180/pi)*atan(y1/far);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          y1=y1+0.5;
          i=i+1;
        }
        if(5<=i<10){                                 //y값이 0.5씩 감소하며 측정
          angle = (180/pi)*atan(y1/far);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          y1=y1-0.5;
          i=i+1;
        }
        if(i==10){
          angle = (180/pi)*atan(y1/far);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
        }
      }
}

void Close_Area_Detecting_Mode()
{
    int times=0;
    LowLevelTime = pulseIn(mainECHO, LOW);
    float y1=0.5;
    float x1=2.5;
    float i=0;
    while(times<=2){
        if(0<=i<3){                                  //x2.5미터 구간에서 y값이 1씩 증가하며 측정
          angle = (180/pi)*atan(y1/x1);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          y1=y1+1;
          i=i+1;
        }
        if(3<=i<5){                                  //y2.5미터 구간에서 x값이 1씩 감소하며 측정
          angle = (180/pi)*atan(y1/x1);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          x1=x1-1;
          i=i+1;
        }
        if(5<=i<8){                                  //y2.5미터 구간에서 x값이 1씩 증가하며 측정
          angle = (180/pi)*atan(y1/x1);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          x1=x1+1;
          i=i+1;
        }
        if(8<=i<10){                                  //x2.5미터 구간에서 y값이 1씩 감소하며 측정
          angle = (180/pi)*atan(y1/x1);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          y1=y1-1;
          i=i+1;
        }
        if(i=10){
          i=0;
          times=times+1;
        }
      }
}





void Sub1_Distance_Mode()
{
  sub1_duration = pulseIn (sub1_ECHO, HIGH);
  sub1_distance = sub1_duration * 17 / 1000; 
}


void Sub2_Distance_Mode()
{
  sub2_duration = pulseIn (sub2_ECHO, HIGH);
  sub2_distance = sub2_duration * 17 / 1000; 
}



void Print_Mode(){
          
          double x = main_distance*cos(angle*pi/205.2);
          double y = main_distance*sin(angle*pi/205.2);
          
          char axis = "현재 좌표는 ";
          char column = "행 ";
          char row = "열";
          char ending = "입니다.";
          char n;
          if(x>4){
            n="5";
            if(0<y<=0.5){
              Serial.println(axis+"1"+column+n+row+ending);
            }
            if(0.5<y<=1){
              Serial.println(axis+"2"+column+n+row+ending);
            }
            if(1<y<=1.5){
              Serial.println(axis+"3"+column+n+row+ending);
            }
            if(1.5<y<=2){
              Serial.println(axis+"4"+column+n+row+ending);
            }
            if(2<y<=2.5){
              Serial.println(axis+"5"+column+n+row+ending);
            }
            if(2.5<y<=3){
              Serial.println(axis+"6"+column+n+row+ending);
            }
          }

          if(3<x<=4){
            n="4";
            if(0<y<=0.5){
              Serial.println(axis+"1"+column+n+row+ending);
            }
            if(0.5<y<=1){
              Serial.println(axis+"2"+column+n+row+ending);
            }
            if(1<y<=1.5){
              Serial.println(axis+"3"+column+n+row+ending);
            }
            if(1.5<y<=2){
              Serial.println(axis+"4"+column+n+row+ending);
            }
            if(2<y<=2.5){
              Serial.println(axis+"5"+column+n+row+ending);
            }
            if(2.5<y<=3){
              Serial.println(axis+"6"+column+n+row+ending);
            }
          }

          if(2<x<=3){
            n="3";
            if(0<y<=1){
              Serial.println(axis+"1"+column+n+row+ending);
            }
            if(1<y<=2){
              Serial.println(axis+"2"+column+n+row+ending);
            }
            if(2<y<=3){
              Serial.println(axis+"3"+column+n+row+ending);
            }
          }
          
          if(1<x<=2){
            n="2";
            if(0<y<=1){
              Serial.println(axis+"1"+column+n+row+ending);
            }
            if(1<y<=2){
              Serial.println(axis+"2"+column+n+row+ending);
            }
            if(2<y<=3){
              Serial.println(axis+"3"+column+n+row+ending);
            }
          }
          
          if(0<x<=1){
            n="1";
            if(0<y<=1){
              Serial.println(axis+"1"+column+n+row+ending);
            }
            if(1<y<=2){
              Serial.println(axis+"2"+column+n+row+ending);
            }
            if(2<y<=3){
              Serial.println(axis+"3"+column+n+row+ending);
            }
          }
} 








// <메인 루프 함수 정의>

void loop() 
{
  //PIR
  if(digitalRead(SIGNAL_PIN) == HIGH) {

    //[ 1st_Area 4~4.5m ]
    far=4.25;
    Far_Area_Detecting_Mode();
    Print_Mode();
    Serial.println("\n\n1구역 인식완료,  2구역 센싱 시작");
        
    //[ 2nd_Area 3~4m ]     
    far=3.5;
    Far_Area_Detecting_Mode();
    Print_Mode();
    Serial.println("\n\n2구역 인식완료,  근접 구역 센싱 시작\n");
    
    //[ 고속 근접 트래킹 모드 우선 활성화 및 근접 영역 감지 ]
    Main_Distance_Mode();
    Sub1_Distance_Mode();
    Sub2_Distance_Mode();
    LowLevelTime = pulseIn(mainECHO, LOW);
      while(LowLevelTime>=45000){               //범위에 인식이 안되는 동안 실행
        High_Speed_Sensing_Mode();              //고속 트래킹 모드 우선 동작,  2.5m 범위에 대상이 없으면 High_Speed_while문 종료
        Close_Area_Detecting_Mode();            //고속 트래킹 대상 없을시 외부 근거리 영역 감지, 인식되면 while문 종료 및 loop문 처음부터 다시 시작.
      }
      Print_Mode();
      Serial.println("\n\n");
      while(angle<70){
        High_Speed_Sensing_Mode();              //범위에 인식이 되어 탈출하면 마지막 구역의 값이 아닐경우 루프
        Close_Area_Detecting_Mode();
        Print_Mode();
      }
      Print_Mode();
      Serial.println("\n\n모든 인식 완료. 초기화 진행");
    }
}
