#include <Servo.h>

// 서보모터 변수 선언
Servo servo;
int servoPin = 3;
int angle = 0;
int cnt = 0;
// 레이저 거리센서 변수 선언
char buff[4]={0x80,0x06,0x03,0x77};
unsigned char data[11]={0};


//-------------------------------------------------------------------------------------------------------------------------------
void setup() {
  // 서보 셋업
  servo.attach(servoPin);
  servo.write(angle);
  // 레이저 셋업
  Serial.begin(115200);
  Serial1.begin(9600);
}

//-------------------------------------------------------------------------------------------------------------------------------

void loop() {
  Serial1.print(buff);
  while(1)
  {
    if (cnt >= 0 && cnt < 10)
    {
      cnt++;
      angle = angle + 10;
      servo.write(angle);
      Serial.print(angle);
      Serial.println("도");
    }
    else if (cnt >= 10 && cnt < 20)
    {
      cnt++;
      angle = angle - 10;
      servo.write(angle);
      Serial.print(angle);
      Serial.println("도");
    }
    else
    {
      cnt = 0;
    }
    if(Serial1.available()>0)//Determine whether there is data to read on the serial 
    {
      delay(10);
      for(int i=0;i<11;i++)
      {
        data[i]=Serial1.read();
      }
      unsigned char Check=0;

      for(int i=0;i<10;i++)
      {
        Check=Check+data[i];
      }
      Check=~Check+1;
      if(data[10]==Check)
      {
        if(data[3]=='E'&&data[4]=='R'&&data[5]=='R')
        {
          Serial.println("Out of range");
        }
        else
        {
          float distance=0;
          distance=(data[3]-0x30)*100+(data[4]-0x30)*10+(data[5]-0x30)*1+(data[7]-0x30)*0.1+(data[8]-0x30)*0.01+(data[9]-0x30)*0.001;
          Serial.print("Distance = ");
          Serial.print(distance,3);
          Serial.println(" M");
        } 
      }
      else
      {
        Serial.println("Invalid Data!");
        float distance=0;
      }
    }
    delay(1000);
  }
}
