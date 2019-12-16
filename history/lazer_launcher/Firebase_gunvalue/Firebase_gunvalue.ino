//FIREBASE SETUP
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
#define WIFI_SSID "Pond"
#define WIFI_PASSWORD "pond2000"

//LCD I2C SET UP
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int health_point = 100;
int Bullet = 200; // Full Amount of Load
int score = 0;
int input; // Signal from Fire button on gun
int Begin_time, Now_time; // Record millisec time that game start
int last_hp;

void Display(){
          Now_time = (millis() - Begin_time)/1000; // Show time while reloading
         

          //Health point(HP) Display
          lcd.setCursor(0,0);
          lcd.print("HP:");
          lcd.setCursor(4,0);
          lcd.print(health_point);
          
        

          //Time Elapse Display
          lcd.setCursor(8,0);
          lcd.print("T:");
          lcd.setCursor(11,0);
          lcd.print(Now_time/60);
          lcd.setCursor(12,0);
          lcd.print(":");
          lcd.setCursor(13,0);
          //clear screen when change unit interger prevent previous number appear.
          if(Now_time%60 == 0){
              lcd.print("0 ");
          }
          else{
              lcd.print(Now_time%60);
          }

       
          
         
          
          //Score display
          
          lcd.setCursor(8,1);
          lcd.print("S: ");
          lcd.setCursor(11,1);
          lcd.print(score);
         
          
    
          //Bullet Left(WP) Display
          lcd.setCursor(0,1);
          lcd.print("WP:");
          lcd.setCursor(4,1);
          lcd.print(Bullet);
          
  
  }

void shoot(){

      Bullet -= input/2;
      digitalWrite(D0, HIGH);
      digitalWrite(D4, HIGH);
      delay(80);
      digitalWrite(D0, LOW);
      digitalWrite(D4, LOW);
      
 
}

void reload(){
     lcd.clear();
     while(Bullet < 200){
      
          Display();
          
          Bullet += 2;
          delay(5);
     }
     lcd.clear();
}

void setup() {

    pinMode(A0, INPUT); // Variable Resistor

    pinMode(D0, OUTPUT); // Laser 

    pinMode(D4, OUTPUT); // Buzzer 

    Serial.begin(115200);

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
 

//Use predefined PINS consts

     Wire.begin(D2, D1);

     lcd.begin();

     lcd.home();

     lcd.print(" LAZERSHOT GAME");

     lcd.setCursor(0,1);
     
     lcd.print(" LOADING");

     for(int i=0; i< 101;i++){
        lcd.setCursor(10,1);
        lcd.print(i);
        lcd.print(" %");
        delay(10);
        lcd.blink();
    }
    delay(3000);
    lcd.clear();

    
    Begin_time = millis()/1000; // Record sec time that game start
    Firebase.setInt("Gun/begin_time", Begin_time);
}

bool sent_end = true;
void loop() { 
  // SCREEN PLAY MODE

    input = analogRead(A0)/100;

    
    if(health_point > 0){
      
         Display();
         
         //shooting function
         if(input > 5){
              shoot();
              health_point--;
              lcd.clear();
         }

         //prevent bullet is minus interger
         if(Bullet < 0){
              Bullet = 0;
         }

         //Automatical Reload 
         if(Bullet == 0 ){
              reload();
         }

    
    }
    //End Game

    
    if(health_point <= 0){
        if(sent_end){
            Firebase.setInt("Gun/End_time", millis()/1000);
            sent_end = false;
        }
        lcd.home();
        lcd.print("   GAME OVER   ");
        lcd.setCursor(0,1);
        lcd.print("YOUR SCORE : ");
        lcd.setCursor(13,1);
        lcd.print(score);
    }
    
    
    
  

}
