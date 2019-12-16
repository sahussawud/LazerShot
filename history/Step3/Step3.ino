
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
#define FIREBASE_AUTH "WtyRAjhqskV3djoq92VaEXonzMTjri9pV0FKUxXH"
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
  pinMode(D0, INPUT);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
}

int randomNum, i=0, score=0, Time=0;

void loop() {
  // set value
  int order;
  digitalWrite(D3, 0);
  digitalWrite(D4, 0);
  digitalWrite(D5, 0);
  order = Firebase.getInt("number");
  if(order==1){
    Serial.println("get it");
    Gameplay3();
  }
}
int Gameplay(){
    randomNum = random(1, 4);
    if(randomNum==1){
      digitalWrite(D3, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D3, 0);
      }
      else if(Time%2==0){
        digitalWrite(D3, 1);
      }
      if(digitalRead(D0)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(1000);
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0);
    }
    else if(randomNum==2){
      digitalWrite(D4, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D4, 0);
      }
      else if(Time%2==0){
        digitalWrite(D4, 1);
      }
      if(digitalRead(D1)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(1000);
      Time++;
      }
      Time=0;
      digitalWrite(D4, 0);
    }
    else if(randomNum==3){
      digitalWrite(D5, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D5, 0);
      }
      else if(Time%2==0){
        digitalWrite(D5, 1);
      }
      if(digitalRead(D2)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(1000);
      Time++;
      }
      Time=0;
      digitalWrite(D5, 0);
    }
    Serial.println(score);
}
void Gameplay2(){
  int i, arr[2];
  for(i=0; i<2; i++){
    arr[i] = random(1, 4);
  }
  if(arr[0]==arr[1]){
    Gameplay();
  }
  else{
     if((arr[0]==1&&arr[1]==2)||(arr[0]==2&&arr[1]==1)){
      digitalWrite(D3, 1);
      digitalWrite(D4, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D3, 0);
        digitalWrite(D4, 0);
      }
      else if(Time%2==0){
        digitalWrite(D3, 1);
        digitalWrite(D4, 1);
      }
      if(digitalRead(D0)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(500);
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0);
      digitalWrite(D4, 0);
      }
     else if((arr[0]==1&&arr[1]==3)||(arr[0]==3&&arr[1]==1)){
      digitalWrite(D3, 1);
      digitalWrite(D5, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D3, 0);
        digitalWrite(D5, 0);
      }
      else if(Time%2==0){
        digitalWrite(D3, 1);
        digitalWrite(D5, 1);
      }
      if(digitalRead(D0)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(500);
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0);
      digitalWrite(D5, 0);
      }
      else if((arr[0]==2&&arr[1]==3)||(arr[0]==3&&arr[1]==2)){
      digitalWrite(D4, 1);
      digitalWrite(D5, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D4, 0);
        digitalWrite(D5, 0);
      }
      else if(Time%2==0){
        digitalWrite(D4, 1);
        digitalWrite(D5, 1);
      }
      if(digitalRead(D0)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(500);
      Time++;
      }
      Time=0;
      digitalWrite(D4, 0);
      digitalWrite(D5, 0);
      }
    }
    Serial.println(score);
}
void Gameplay3(){
  int i, arr[3];
  for(i=0; i<2; i++){
    arr[i] = random(1, 4);
  }
  if(arr[0]==arr[1]==arr[2]){
    Gameplay();
  }
  else if((arr[0]==1||1==arr[1]||arr[2]==1)&&(arr[0]==2||2==arr[1]||arr[2]==2)&&(arr[0]==3||3==arr[1]||arr[2]==3)){
        digitalWrite(D3, 1);
        delay(500);
        digitalWrite(D4, 1);
        delay(500);
        digitalWrite(D5, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D3, 0);
        delay(500);
        digitalWrite(D4, 0);
        delay(500);
        digitalWrite(D5, 0);
      }
      else if(Time%2==0){
        digitalWrite(D3, 1);
        delay(500);
        digitalWrite(D4, 1);
        delay(500);
        digitalWrite(D5, 1);
      }
      if(digitalRead(D2)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(1000);
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0);
      delay(500);
      digitalWrite(D4, 0);
      delay(500);
      digitalWrite(D5, 0);
  }
  else if((arr[0]==1||1==arr[1]||arr[2]==1)&&(arr[0]==2||2==arr[1]||arr[2]==2)){
        digitalWrite(D3, 1);
        delay(500);
        digitalWrite(D4, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D3, 0);
        delay(500);
        digitalWrite(D4, 0);
      }
      else if(Time%2==0){
        digitalWrite(D3, 1);
        delay(500);
        digitalWrite(D4, 1);
      }
      if(digitalRead(D2)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(500);
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0);
      delay(500);
      digitalWrite(D4, 0);
  }
  else if((arr[0]==1||1==arr[1]||arr[2]==1)&&(arr[0]==3||3==arr[1]||arr[2]==3)){
        digitalWrite(D3, 1);
        delay(500);
        digitalWrite(D5, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D3, 0);
        delay(500);
        digitalWrite(D5, 0);
      }
      else if(Time%2==0){
        digitalWrite(D3, 1);
        delay(500);
        digitalWrite(D5, 1);
      }
      if(digitalRead(D2)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(500);
      Time++;
      }
      Time=0;
      digitalWrite(D3, 0);
      delay(500);
      digitalWrite(D5, 0);
  }
  else if((arr[0]==3||3==arr[1]||arr[2]==3)&&(arr[0]==2||2==arr[1]||arr[2]==2)){
        digitalWrite(D5, 1);
        delay(500);
        digitalWrite(D4, 1);
      while(1){
      if(Time%2!=0){
        digitalWrite(D5, 0);
        delay(500);
        digitalWrite(D4, 0);
      }
      else if(Time%2==0){
        digitalWrite(D5, 1);
        delay(500);
        digitalWrite(D4, 1);
      }
      if(digitalRead(D2)==1){
        score++;
        break;
      }
      else if(Time==5){
        break;
      }
      delay(500);
      Time++;
      }
      Time=0;
      digitalWrite(D5, 0);
      delay(500);
      digitalWrite(D4, 0);
  }
    Serial.println(score);
}
