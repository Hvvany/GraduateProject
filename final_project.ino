//서보 변수 정의
#include <Servo.h>
#include <math.h>

Servo servo;
int servoPin = 9;
int angle = 0;


//Main 초음파 변수 정의
#define  Measure  1     // Mode select
int mainTRIG = 2;       // PWM trigger pin
int mainECHO = 3;       // PWM Output 0-25000US,Every 50US represent 1cm
/*
int sensorPin = A0;     // select the input pin for the potentiometer
int sensorValue = 0;    // variable to store the value coming from the sensor
*/
unsigned int main_distance= 0;

//Sub1 초음파 변수 정의
#define sub1_TRIG 5     // TRIG 핀 설정 (초음파 보내는 핀)
#define sub1_ECHO 6     // ECHO 핀 설정 (초음파 받는 핀)
long sub1_duration, sub1_distance;

//Sub2 초음파 변수 정의
#define sub2_TRIG 7     // TRIG 핀 설정 (초음파 보내는 핀)
#define sub2_ECHO 8     // ECHO 핀 설정 (초음파 받는 핀)
long sub2_duration, sub2_distance;


//pir 변수 정의
#define SIGNAL_PIN 4


//삼각함수 공식 정의
const double pi = 3.1415926;


float far;





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















    

//  < 참조 함수 정의 > 
void Main_Distance_Mode()                             // main_distance 값 구하기 함수 (cm 단위)
{
  digitalWrite(mainTRIG, LOW);
  digitalWrite(mainTRIG, HIGH);                       // reading Pin PWM will output pulses 
  if(Measure){
    unsigned long LowLevelTime = pulseIn(mainECHO, LOW);
    
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
    float y1=0.25;
    float i=0;
      while(LowLevelTime>=45000){
        if(0<=i<5){                                  //y값이 0.5씩 증가하며 측정
          angle = (180/pi)*atan(y1/far);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          y1=y1+0.5;
          i = i+1;
        }
        if(5<=i<10){                                 //y값이 0.5씩 감소하며 측정
          angle = (180/pi)*atan(y1/far);
          angle = angle*1.14;
          servo.write(angle);
          delay(50);
          Main_Distance_Mode();
          LowLevelTime = pulseIn(mainECHO, LOW);
          y1=y1-0.5;
          i = i+1;
        }
        if(i==10){
          i=0;
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
          Serial.println("\n\n\n\nx = ");
          double x = main_distance*cos(angle*pi/205.2);
          Serial.print(x);
          Serial.println("\rcm \ny = ");
          double y = main_distance*sin(angle*pi/205.2);
          Serial.print(y);
          Serial.println("\rcm");
          Serial.println("\n각도 = ");
          Serial.print(angle);
          Serial.println("\n거리 = ");
          Serial.print(main_distance);
          Serial.println("cm");
          
          delay(1000);
      }




// <메인 루프 함수 정의>
void loop(){
  //PIR
  if(digitalRead(SIGNAL_PIN) == HIGH) {

    //[ 1st_Area 4~4.5m ]
    far=4.25;
    Far_Area_Detecting_Mode();
    Print_Mode();
        
    //[ 2nd_Area 3~4m ]     
    far=3.5;
    Far_Area_Detecting_Mode();
    Print_Mode();
    
    //[ 고속 근접 트래킹 모드 우선 활성화 및 근접 영역 감지 ]
    if(main_distance<=250&&sub1_distance<=250&&sub2_distance<=250){
      
    }
  }
}
