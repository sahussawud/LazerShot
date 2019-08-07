
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lazershotkmitl.firebaseio.com"
#define FIREBASE_AUTH "WtyRAjhqskV3djoq92VaEXonzMTjri9pV0FKUxXH"
#define WIFI_SSID "DOUBLE_R0"
#define WIFI_PASSWORD "Dr20436527"

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
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
}
 /* ประกาศตัวแปร โดย randomNum คือ ตัวเลขที่จะสุ่ม i สำหรับ for loop score เอาไว้เก็บคะแนน Time คือเก็บค่าให้ไฟค้างไว้เป็นจำนวนรอบ
 timeshoot คือเวลาที่ค้างไว้ต่อ1รอบTime timechange คือเวลารอที่จะเปลี่ยนสุมครั้งถัดไป 
 stax เอาไว้เก็บไฟที่โดนยิง life พลังชีวิตผู้เล่น order ลำดับที่บอร์ดตัวลูกจะทำงาน counter ตัวนับว่าถึงstateไหนแล้ว */
int randomNum, i=0, score=0, Time=0;
int timeshoot[6]={600, 500, 400, 300}, timechange[6]={1000, 700, 500, 200};
int stax, life;
int order, order2, order3, counter;

void loop() {
  // set value
  digitalWrite(D3, 0);
  digitalWrite(D4, 0);
  digitalWrite(D5, 0);
  // ดึงข้อมูลจาก Firebase
  life = Firebase.getInt("lifepoint");
  order = Firebase.getInt("ran/ran_1");
  order2 = Firebase.getInt("ran/ran_2");
  order3 = Firebase.getInt("ran/ran_3");
  // เช้คว่าค่าที่ส่งมาทาง order ตรงกับ เลขบอร์ดของตัวเองรึป่าว
  counter = Firebase.getInt("count");
  if(order==1||order2==1||order3==1){
    digitalWrite(D6, 1);
    delay(500);
    digitalWrite(D6, 0);
    Serial.println("get it");
    if(counter==0){
      Firebase.setInt("score/score_1", score); // จบเกมและส่งคะแนน
      Firebase.setInt("lifepoint", 0); // จบเกมและส่งlife
      score = 0; // รีเซ็ตคะแนน
    }
    else if(counter==1){
      Gameplay(timeshoot[0], timechange[0]); // รัน state แรก
    }
    else if(counter==2){
      Gameplay2(timeshoot[0], timechange[0]); // รัน state สอง
    }
    else if(counter==3){
      Gameplay3(timeshoot[0], timechange[0]); // รัน state ที่สาม
    }
    else if(counter==4){
      Gameplay3(timeshoot[2], timechange[1]); // รัน state ที่สี่
    }
    else if(counter==5){
      Gameplay2(timeshoot[2], timechange[2]); // รัน state ที่ห้า
    }
    else {
      Gameplay(timeshoot[3], timechange[3]); // รันไปเรื่อยๆ
    }
  }
}
void Gameplay(int timeshoot, int timechange){ // ฟังก์ชั่นแรก เปิดแค่ไฟตัวหลอดเดียว
    randomNum = random(1, 4); // สุ่มตัวเลข
    if(randomNum==1){ // ถ้าสุ่มได้เลข 1 จะทำ if นี้
      digitalWrite(D3, 1); // led เปิด
      while(1){ // loop รันรอรับสัญญาณ เลเซอร์
      if(digitalRead(D0)==1){
        score++;  // ถ้าได้รับเลเซอร์ จะบวกคะแนน
        break;
      }
      else if(Time==10){
        life++; // เมื่อ loop รันครบห้ารอบ พลังชีวิตจะลด และสุ่มหลอดใหม่
        Firebase.setInt("lifepoint", life); // ส่งค่าพลังชีวิตขึ้น Firebase
        break;
      }
      delay(timeshoot/2); // เวลาค้างให้ยิง
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0); // รีเซตทุกอย่าง
      delay(timechange); // เวลาหน่วงก่อนจะสุ่มใหม่
    }
    else if(randomNum==2){
      digitalWrite(D4, 1);
      while(1){
      if(digitalRead(D1)==1){
        score++;
        break;
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      digitalWrite(D4, 0);
      delay(timechange);
    }
    else if(randomNum==3){
      digitalWrite(D5, 1);
      while(1){
      if(digitalRead(D2)==1){
        score++;
        break;
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      digitalWrite(D5, 0);
      delay(timechange);
    }
    Serial.println(score);
}
void Gameplay2(int timeshoot, int timechange){ // เปิดไฟพร้อมกัน 2 หลอด
  int arr[2]; // สร้าง array มาเก็บ 2 ค่า
  for(i=0; i<2; i++){
    arr[i] = random(1, 4);
  }
  if(arr[0]==arr[1]){ // ถ้าเลขซ้ำกันให้ไปใช้ function หลอดเดียว
    Gameplay(timeshoot, timechange);
  }
  else{
     if((arr[0]==1&&arr[1]==2)||(arr[0]==2&&arr[1]==1)){
      digitalWrite(D3, 1);
      digitalWrite(D4, 1);
      while(1){
      if(stax >= 2){
        break;
      }
      if(digitalRead(D0)==1){ // ถ้ายิงโดดจะดับทีละหลอด
        score++;
        stax++;
        digitalWrite(D3, 0);
      }
      if(digitalRead(D1)==1){
        score++;
        stax++;
        digitalWrite(D4, 0);
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax = 0;
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      delay(timechange);
      }
     else if((arr[0]==1&&arr[1]==3)||(arr[0]==3&&arr[1]==1)){
      digitalWrite(D3, 1);
      digitalWrite(D5, 1);
      while(1){
      if(stax >= 2){
        break;
      }
      if(digitalRead(D0)==1){
        score++;
        stax++;
        digitalWrite(D3, 0);
      }
      if(digitalRead(D2)==1){
        score++;
        stax++;
        digitalWrite(D5, 0);
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax = 0;
      digitalWrite(D3, 0);
      digitalWrite(D5, 0);
      delay(timechange);
      }
      else if((arr[0]==2&&arr[1]==3)||(arr[0]==3&&arr[1]==2)){
      digitalWrite(D4, 1);
      digitalWrite(D5, 1);
      while(1){
      if(stax >= 2){
        break;
      }
      if(digitalRead(D1)==1){
        score++;
        stax++;
        digitalWrite(D4, 0);
      }
      if(digitalRead(D2)==1){
        score++;
        stax++;
        digitalWrite(D5, 0);
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax = 0;
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      delay(timechange);
      }
    }
    Serial.println(score);
}
void Gameplay3(int timeshoot, int timechange){ // เปิดทีละ 3 หลอด และ 2 หลอด
  int i, arr[3]; // สร้าง array มาเก็บ 3 ค่า
  for(i=0; i<2; i++){
    arr[i] = random(1, 4);
  }
  if(arr[0]==arr[1]==arr[2]){ // ถ้า 3 ค่าเหมือนกันให้ใช้ function 
    Gameplay(timeshoot, timechange);
  }
  else if((arr[0]==1||1==arr[1]||arr[2]==1)&&(arr[0]==2||2==arr[1]||arr[2]==2)&&(arr[0]==3||3==arr[1]||arr[2]==3)){
        digitalWrite(D3, 1);
        digitalWrite(D4, 1);
        digitalWrite(D5, 1);
      while(1){
      if(digitalRead(D2)==1){
        score++;
        stax++;
        digitalWrite(D5, 0);
      }
      if(digitalRead(D0)==1){
        score++;
        stax++;
        digitalWrite(D3, 0);
      }
      if(digitalRead(D1)==1){
        score++;
        stax++;
        digitalWrite(D4, 0);
      }
      if(stax>=3){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      else if(Time==10){
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax = 0;
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      delay(timechange);
  }
  else if((arr[0]==1||1==arr[1]||arr[2]==1)&&(arr[0]==2||2==arr[1]||arr[2]==2)){
        digitalWrite(D3, 1);
        digitalWrite(D4, 1);
      while(1){
      if(digitalRead(D0)==1){
        score++;
        stax++;
        digitalWrite(D3, 0);
      }
      if(digitalRead(D1)==1){
        score++;
        stax++;
        digitalWrite(D4, 0);
      }
      if(stax>=2){
        break;
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax=0;
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      delay(timechange);
  }
  else if((arr[0]==1||1==arr[1]||arr[2]==1)&&(arr[0]==3||3==arr[1]||arr[2]==3)){
        digitalWrite(D3, 1);
        digitalWrite(D5, 1);
      while(1){
      if(digitalRead(D0)==1){
        score++;
        stax++;
        digitalWrite(D3, 0);
      }
      if(digitalRead(D2)==1){
        score++;
        stax++;
        digitalWrite(D5, 0);
      }
      if(stax>=2){
        break;
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax=0;
      digitalWrite(D3, 0);
      digitalWrite(D5, 0);
      delay(timechange);
  }
  else if((arr[0]==3||3==arr[1]||arr[2]==3)&&(arr[0]==2||2==arr[1]||arr[2]==2)){
        digitalWrite(D4, 1);
        digitalWrite(D5, 1);
      while(1){
      if(digitalRead(D1)==1){
        score++;
        stax++;
        digitalWrite(D4, 0);
      }
      if(digitalRead(D2)==1){
        score++;
        stax++;
        digitalWrite(D5, 0);
      }
      if(stax>=2){
        break;
      }
      else if(Time==10){
        life++;
        Firebase.setInt("lifepoint", life);
        break;
      }
      delay(timeshoot/2);
      Time++;
      }
      Time=0;
      stax=0;
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      delay(timechange);
  }
    Serial.println(score);
}
