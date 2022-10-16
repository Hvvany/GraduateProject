


void setup() {

  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);

}



void loop()



{


  pinMode(3, OUTPUT);
  digitalWrite(3, HIGH);
  delay(500);

  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  delay(500);

}
