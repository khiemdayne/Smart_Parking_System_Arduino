void setup() {
  // put your setup code here, to run once:
  pinMode(0,OUTPUT);
   pinMode(1,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(0,0);
  digitalWrite(1,1);
  delay(2000);
  digitalWrite(1,0);
  delay(2000);
}
