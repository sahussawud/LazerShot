void setup() {
  // put your setup code here, to run once:
pinMode(D0, INPUT);
Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int st;
  st = digitalRead(D0);
  delay(1000);
  Serial.println(st);
}
