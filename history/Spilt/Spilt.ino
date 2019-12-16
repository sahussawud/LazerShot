void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

int num, num2, num3;
String txt = "02,03,1500";

void loop() {
  // put your main code here, to run repeatedly:
  spilt(txt);
  Serial.println(num);
  Serial.println(num2);
  Serial.println(num3);
  delay(1000);
}
void spilt(String txt){
  String txt2, txt3, txt4;
  txt4 = txt.substring(0, 2);
  Serial.println(txt4);
  txt2 = txt.substring(3, 5);
  Serial.println(txt2);
  txt3 = txt.substring(6);
  Serial.println(txt3);
  num2 = txt2.toInt();
  num3 = txt3.toInt();
  num = txt4.toInt();
}
