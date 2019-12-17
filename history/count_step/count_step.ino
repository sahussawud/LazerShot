
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

int score_1, score_2, score_3, score_4, censcore=0, life=0;


#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lazershotkmitl.firebaseio.com"
#define FIREBASE_AUTH "WtyRAjhqskV3djoq92VaEXonzMTjri9pV0FKUxXH"
#define WIFI_SSID "DOUBLE_R0"
#define WIFI_PASSWORD "Dr20436527"

<<<<<<< HEAD
/*#define WIFI_SSID "kit"
#define WIFI_PASSWORD "kit314159"*/
=======
// #define WIFI_SSID "kit"
// #define WIFI_PASSWORD "kit314159"
>>>>>>> be804d5762bc0b513a523e8af583780c822577cc

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
    int check = Firebase.getInt("begin_state");
    if(check == 1){
      break;
    }
    else{
      Serial.print("Pls wait : ");
      Serial.println(check);
    }
  }
  //run time
  for(int i=1; i<7; i+=1){
    Firebase.setInt("ran_1", random(1, 3));
    Firebase.setInt("ran_2", random(1, 3));
    Firebase.setInt("ran/ran_3", random(1, 3));
    if(i>=5){
       Firebase.setInt("ran_3", random(1, 3));
    }
    Serial.print("Count ");
    Serial.println(i);
    Firebase.setInt("count", i);
    for(int s=0; s<5; s+=1){
      //check lifepoint realtime
      if(Firebase.getInt("lifepoint")==100){
         Firebase.setInt("count", 0);
      }
      //test 
      Serial.println(s);
      Serial.print("      ");
      Serial.print(Firebase.getInt("board/board_3"));
      Serial.println();
      delay(1000);
    }
  }

  //total score up to firebase
  censcore += Firebase.getInt("score/score_1");
  censcore += Firebase.getInt("score/score_2");
  censcore += Firebase.getInt("score/score_3");
  censcore += Firebase.getInt("score/score_4");
  Firebase.setInt("score/censcore", censcore);

  //set bact to defult
  Firebase.setInt("ran_1", 0);
  Firebase.setInt("ran_2", 0);
  Firebase.setInt("ran_3", 0);
}