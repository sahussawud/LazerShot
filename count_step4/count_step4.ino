
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

int score_1, score_2, score_3, score_4, censcore=0, life=0, i=0, counter=0;
unsigned long Showtime, Thistime; // ประกาศตัวแปรชื่อ ShowTime เก็บค่าการนับเวลา เป็นตัวแปร unsigned long


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lazershotkmitl.firebaseio.com"
#define FIREBASE_AUTH "WtyRAjhqskV3djoq92VaEXonzMTjri9pV0FKUxXH"
//#define WIFI_SSID "iPhone ของ Punyapat"
//#define WIFI_PASSWORD "kit127kub"

#define WIFI_SSID "DOUBLE_R0"
#define WIFI_PASSWORD "Dr20436527"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
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
}

void loop() {
  while(true){
    int check = Firebase.getInt("begin_state/state");
    if(check == 1){
      break;
    }
    else{
      Serial.print("Pls wait : ");
      Serial.println(check);
    }
  }
  
  //run game
  while(true){
    //check lifepoint for set all
    if (Firebase.getInt("lifepoint") >= 20){
        //print check
        Serial.print("Lifepoint : ");
        Serial.println(Firebase.getInt("lifepoint"));
        Firebase.setInt("lifepoint", 0); // รีเซ็ตพลังชีวิต
        break;
    }
    Firebase.setInt("ran/ran_1", random(1, 5));
    counter = 1;
    if (i >= 59)                                    //second minute start sheet2 
       Firebase.setInt("ran/ran_2", random(1, 5));
       counter = 2;
    if (i >= 99)                                   //third minute start sheet3
       Firebase.setInt("ran/ran_3", random(1, 5));
       counter = 4;
    //print check
    Serial.print("Count ");
    Serial.println(i);
    Firebase.setInt("count", counter);
    
    

    // 5 sec for check count
    for(int s=0; s<5; s+=1){
      i+=1;
      if(Firebase.getInt("lifepoint") >= 20){  //check lifepoint realtime
         totalscore();
         setzero();
         i=0;
         break;
      }
      Serial.println(s);  //print check
      timer();
    }
  }
}


void totalscore(){
      String key = Firebase.getString("latest_key/key"); // เอา key ผู้เล่นมา
      //total score up to firebase
      censcore = Firebase.getInt("score/score_1")+Firebase.getInt("score/score_2")+Firebase.getInt("score/score_3")+Firebase.getInt("score/score_4");
      Firebase.setInt("users/"+key+"/score", censcore); // up score to user
      Firebase.setInt("score/censcore", censcore);

      Firebase.setInt("score/score_1", 0);
      Firebase.setInt("score/score_2", 0);
      Firebase.setInt("score/score_3", 0);
      Firebase.setInt("score/score_4", 0);
}

void setzero(){
      Firebase.setInt("count", 0); // ส่ง count = 0 แปลว่าจบเกม
      Firebase.setInt("begin_state/state", 0); // เปลี่ยน ค่าเพื่อรอผู้เล่นใหม
      Firebase.setInt("ran/ran_1", 0);
      Firebase.setInt("ran/ran_2", 0);
      Firebase.setInt("ran/ran_3", 0);
      counter = 0;
}

void timer(){
      Showtime = millis();
      while(true){
        Thistime = millis();
        delay(10);
        if(Thistime/1000-Showtime/1000>=1){
          //Serial.println(Thistime-Showtime);
          Serial.println("Stop");
          break;
        }
      }
}
