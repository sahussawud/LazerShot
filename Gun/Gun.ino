#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

int Bullet;


Adafruit_SSD1306 display(-1);

// constants won't change. They're used here to set pin numbers:

#define trigger_pin  2
//D1 ,D2 reserve for oled

#define back_button_pin  6
#define front_button_pin  7

#define laser_pin 5  // D5 connect to GND , Vin Conect to VCC 

const int speaker_pin = 8;
const int back_motor = 3;
const int front_motor = 4;

int t_back,t_front;

      

void setup() {
    // initialize the LED pin as an output:
    Serial.begin(9600);
    pinMode(trigger_pin, INPUT);//Trigger Gun when not push trigger it's "False";
    //Reserve D1, D2 for OLED PINs
    //Back button for RELOAD F(X); HIT "FALSE" NOT HIT "TRUE"
    pinMode(back_button_pin, INPUT);
    //Front Button for RELOAD F(x); HIT "FALSE" NOT HIT "TRUE"
    pinMode(front_button_pin, INPUT);

    //LASER COMMAND PIN ON in "FALSE" OFF "TRUE";
    //NOTE : D5 Pair with Laser Ground Wire 
    pinMode(laser_pin, OUTPUT);

    //Command Buzzer
    pinMode(speaker_pin, OUTPUT);

    //vibration module command VCC 0 is close 1 is open
    pinMode(front_motor, OUTPUT); //HIGH TO ACTIVE , LOW TO CLOSE 3.3V
    pinMode(back_motor, OUTPUT); //HIGH TO CLOSE , LOW TO CLOSE 5V

    // initialize with the I2C addr 0x3C
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

    // Clear the buffer.
    display.clearDisplay();

    
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.println("Lazer Shot");
  
      display.setTextSize(1);
      display.print("loading");
      display.setTextSize(1);
      for(int i = 1; i < 14; i++){
        display.setTextSize(1);
        display.print("#");
        delay(500);
        display.display();  
      }
        display.println("");
      delay(2000);

      
      display.setTextColor(BLACK, WHITE);
      display.setTextSize(1);
      display.println(" Trigger To Unlock  ");

      display.setTextColor(WHITE, BLACK);
      display.display();

      while(0.){
        if(!digitalRead(trigger_pin)){
            break;
        }
      }
        
      display.clearDisplay();
      display.display();
    

     Bullet = 200;

}

void loop() {

      
      int Trigger = digitalRead(trigger_pin);
      //Set default laser ground to HIGH make it OFF state;
      digitalWrite(laser_pin, HIGH);
      display.clearDisplay();

      display.setCursor(0,0);
      display.setTextSize(1);
      display.setTextColor(WHITE,BLACK);
      display.println(" WEAPON ID: P6O4N8D9");


      display.setTextColor(WHITE);
      display.setTextSize(3);
      display.print(Bullet);
      display.println("/200");

      display.display();

      
        
      

      //not done
      if(Trigger && Bullet > 0){
            Bullet -= 2;
            //Laser On 
            digitalWrite(laser_pin, LOW);
            //Buzzer On
              for (int i=2000; i<8000; i=i*1.02) { 
                      tone(speaker_pin,i,45); 
              } 
              for (int i=1; i>5000; i=i*.98) {
                      tone(speaker_pin,i,45);
              }
                      tone(speaker_pin,10000,300);
            digitalWrite(front_motor, HIGH);
            digitalWrite(back_motor, LOW);
            delay(50);
            //Both OFF
            digitalWrite(laser_pin, HIGH);
            
            
            delay(50);
            display.clearDisplay();
            
           
      }
      if(!Trigger){
            digitalWrite(front_motor, LOW);
            digitalWrite(back_motor, HIGH); 
      }


       if(Bullet < 0){
          Bullet = 0;
      }

      //back button
      if(!digitalRead(back_button_pin)){
            t_back = millis();
            Serial.println("t_back");
      }

      //front button
      if(!digitalRead(front_button_pin)){
            t_front = millis();
            Serial.println("f_front");
      }
      
      int between_t = abs(t_back - t_front)%10000; 

      //check for RELOAD 
            
        if(between_t < 500 && Bullet < 200){
   
            Bullet += 5;
            t_back = 0;
            t_front = 0;
            //Buzzer On    
            for (int i=1; i<3000; i=i*1.02) { 
                      tone(speaker_pin,i,45); 
            }
            for (int i=3000; i<1; i=i*1.02) { 
                      tone(speaker_pin,i,45); 
            }
            
            if(Bullet > 200){ 
              Bullet = 200;
            }
            
      }
      
      

}
