unsigned long Showtime, Thistime; // ประกาศตัวแปรชื่อ ShowTime เก็บค่าการนับเวลา เป็นตัวแปร unsigned long

void setup(){
Serial.begin(9600);
}
void loop(){
  Showtime = millis();
  while(1){
    Thistime = millis();
    delay(10);
    if(Thistime/1000-Showtime/1000>=2){
      Serial.println(Thistime-Showtime);
      Serial.println("Stop");
      break;
    }
  }
  Serial.println("Finish");
}
