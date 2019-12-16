
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

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "lazershotkmitl.firebaseio.com"
#define FIREBASE_AUTH **********************************
#define WIFI_SSID "Pond"
#define WIFI_PASSWORD "pond2000"

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

  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, INPUT);
  pinMode(D4, INPUT);
}

int pre_1, pre_2, pre_3;

void loop() {
  // set value
  int point1 = analogRead(D0);
  int point2 = analogRead(D1);
  int point3 = analogRead(D2);
  int point4 = analogRead(D3);
  int point5 = analogRead(D4);


  if(point1){
    Firebase.setString("text" , "เป้าเเรกถูกยิง");
   }
  if(point2){
    Firebase.setString("text" , "เป้าสองถูกยิง");
   }
  if(point3){
    Firebase.setString("text" , "เป้าสามถูกยิง");
   }

  
}
