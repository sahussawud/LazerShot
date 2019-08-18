void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

String txt2, txt3, txt4;
String txt = "02,03,1500";

void loop() {
  // put your main code here, to run repeatedly:
  txt2 = txt.substring(0, 2);
  Serial.println(txt2);
  delay(1000);
  txt3 = txt.substring(3, 5);
  Serial.println(txt3);
  delay(1000);
  txt4 = txt.substring(6);
  Serial.println(txt4);
  delay(1000);
}
