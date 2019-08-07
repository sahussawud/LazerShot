unsigned long Showtime, Thistime; // ประกาศตัวแปรชื่อ ShowTime เก็บค่าการนับเวลา เป็นตัวแปร unsigned long

void setup(){
Serial.begin(9600);
}
void loop(){
  Showtime = millis();
  while(1){
    Thistime = millis();
    delay(1);
    if(Thistime/1000-Showtime/1000>=5){
      Serial.println(Thistime-Showtime);
      Serial.println("Stop");
      break;
    }
  }
}
