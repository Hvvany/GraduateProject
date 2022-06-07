#include <Servo.h>

Servo servo;
int servoPin = 9;
float angle = 0;

#define  Measure  1     //Mode select
int URECHO = 3;         // PWM Output 0-25000US,Every 50US represent 1cm
int URTRIG = 2;         // PWM trigger pin

unsigned int DistanceMeasured= 0;
 








void setup() {
  servo.attach(servoPin);
  servo.write(angle);

  //Serial initialization
  Serial.begin(9600);                        // Sets the baud rate to 9600
  pinMode(URTRIG,OUTPUT);                    // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                 // Set to HIGH
  pinMode(URECHO, INPUT);                    // Sending Enable PWM mode command
  delay(500);
  Serial.println("\n\n\n센서 테스트 완료...");
}


void loop() {
    servo.write(angle);
    for(; angle < 102.6; angle){
      servo.write(angle);
      
      PWM_Mode();
      int d1 = DistanceMeasured;
      /*
      PWM_Mode();
      int d2 = DistanceMeasured;
      
      int m1 = (d1*0.9+d2*0.1)/2;
      Serial.println("\nm1");
      Serial.print(m1);
      */
      angle = angle + 20;
      servo.write(angle);
      
      
      PWM_Mode();
      int d3 = DistanceMeasured;
      /*
      PWM_Mode();
      int d4 = DistanceMeasured;
      
      int m2 = (d3*0.9+d4*0.1)/2;
      Serial.println("\nm2");
      Serial.print(m2);
      */
      
      if(0<d1<=200&&d3!=0){
      int gap = d1 - d3;
      Serial.println("\ngap");
      Serial.print(gap);
      
      
    
      
        if(gap<-5){
          Serial.println("\n비교문");
          break;
        }
      }
      angle = angle + 20;
    }
     

    for(; angle > 0; angle){
      servo.write(angle);
      
      
      PWM_Mode();
      int d1 = DistanceMeasured;
      
      /*PWM_Mode();
      int d2 = DistanceMeasured;
      int m1 = (d1*0.9+d2*0.1)/2;
      Serial.println("\nm1_2");
      Serial.print(m1);
      */
      
      angle = angle - 20;
      servo.write(angle);
      
      
      PWM_Mode();
      int d3 = DistanceMeasured;
      
      /*PWM_Mode();
      int d4 = DistanceMeasured;
      int m2 = (d3*0.9+d4*0.1)/2;
      Serial.println("\nm2_2");
      Serial.print(m2);
      */
      if(0<d1<=200&&d3!=0){
      int gap = d1 - d3;
      Serial.println("\ngap");
      Serial.print(gap);
      
      
      
        if(gap<-5){
          Serial.println("\n비교문");
          break;
        }
      }
      angle = angle - 20;
    }
}
    


void PWM_Mode()                              // a low pull on pin COMP/TRIG  triggering a sensor reading
{
  Serial.print("\nDistance Measured=");
  digitalWrite(URTRIG, LOW);
  digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses 
  if( Measure)
  {
    unsigned long LowLevelTime = pulseIn(URECHO, LOW) ;
    delay(500);
    DistanceMeasured = LowLevelTime /50;   // every 50us low level stands for 1cm
    Serial.print(DistanceMeasured);
    Serial.println("cm");
  }
 
  }
 
