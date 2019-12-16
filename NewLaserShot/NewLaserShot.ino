#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "Test-project.firebaseio.com"
#define FIREBASE_AUTH "AIzaSyD0w-irpqrf9HKPppaCX-rnKkRV3AdI1eg"
#define WIFI_SSID "DOUBLE_R0"
#define WIFI_PASSWORD "Dr20436527"
Thread* myThread = new Thread();

void setup() {
  Serial.begin(9600);
  // เชื่อมต่อ WIFI
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(D3, OUTPUT);
}
 /* ประกาศตัวแปร โดย randomNum คือ ตัวเลขที่จะสุ่ม i สำหรับ for loop score เอาไว้เก็บคะแนน Time คือเก็บค่าให้ไฟค้างไว้เป็นจำนวนรอบ
 timeshoot คือเวลาที่ค้างไว้ต่อ1รอบTime timechange คือเวลารอที่จะเปลี่ยนสุมครั้งถัดไป 
 stax เอาไว้เก็บไฟที่โดนยิง life พลังชีวิตผู้เล่น order ลำดับที่บอร์ดตัวลูกจะทำงาน counter ตัวนับว่าถึงstateไหนแล้ว */

void loop() {
  // set value
  analogWrite(D3, 0);
  // ดึงข้อมูลจาก Firebase
  Board = Firebase.getInt("Board");
  // เช้คว่าค่าที่ส่งมาทาง Board ตรงกับ เลขบอร์ดของตัวเองรึป่าว
  if(Board==1){
    Gameplay();  
    }
  }


void Gameplay(){ // ฟังก์ชั่นแรก เปิดแค่ไฟตัวหลอดเดียว
    randomNum = random(1, 4); // สุ่มตัวเลข
    if(randomNum==1){ // ถ้าสุ่มได้เลข 1 จะทำ if นี้
      Showtime = millis();
      analogWrite(D3, 255); // led เปิด
      while(1){ // loop รันรอรับสัญญาณ เลเซอร์
          Thistime = millis();
          delay(1);
       if(Thistime/1000-Showtime/1000>=1000){
          analogWrite(D3, 0);
          Serial.println(Thistime-Showtime/1000);
          Serial.println("Stop");
          Firebase.setInt("lifepoint", life);
          break;
       }
        score = Firebase.getInt("Score");
        score++;  // ถ้าได้รับเลเซอร์ จะบวกคะแนน
        Firebase.setInt("Score, score);
        break;
      }
    }
      delay(1000); // เวลาหน่วงก่อนจะสุ่มใหม่
  }
}
