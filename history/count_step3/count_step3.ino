
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

int score_1, score_2, score_3, score_4, censcore=0, life=0, i=0;


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
    if (Firebase.getInt("lifepoint") >= 10){
        //print check
        Serial.print("    ");
        Serial.println(Firebase.getInt("lifepoint"));
        Firebase.setInt("lifepoint", 0); // รีเซ็ตพลังชีวิต
        break;
    }
    Firebase.setInt("ran/ran_1", random(1, 5));
    Firebase.setInt("ran/ran_2", random(1, 5));
    if(i>=5){
       Firebase.setInt("ran/ran_3", random(1, 5));
    }
    //print check
    Serial.print("Count ");
    Serial.println(i);
    Firebase.setInt("count", i);
    i+=1;

    // 5 sec for check count
    for(int s=0; s<5; s+=1){
      //check lifepoint realtime
      if(Firebase.getInt("lifepoint") >= 10){
         Firebase.setInt("count", 0); // ส่ง count = 0 แปลว่าจบเกม
         Firebase.setInt("begin_state/state", 0); // เปลี่ยน ค่าเพื่อรอผู้เล่นใหม่
         
         Firebase.setInt("ran/ran_1", 0);
         Firebase.setInt("ran/ran_2", 0);
         Firebase.setInt("ran/ran_3", 0);
         i = 0;
         String key = Firebase.getString("latest_key/key"); // เอา key ผู้เล่นมา
         //total score up to firebase
         censcore += Firebase.getInt("score/score_1");
         censcore += Firebase.getInt("score/score_2");
         censcore += Firebase.getInt("score/score_3");
         censcore += Firebase.getInt("score/score_4");
         Firebase.setInt("users/"+key+"/score", censcore); // up score to user
         break;
      }
      //print check 
      Serial.println(s);
      delay(1000);
    }
  }
}
