
#define SIGNAL_PIN 8

void setup() {
  Serial.begin(9600);
  pinMode(SIGNAL_PIN, INPUT);
}

void loop() {
  if(digitalRead(SIGNAL_PIN) == HIGH) {
  Serial.println("Person was detected!");
 }else{
  Serial.println("NO PERSON");
}
  delay(1000);
}
