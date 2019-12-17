#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "la330";
const char* password = "33333330";
const char* mqtt_server = "broker.mqttdashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int val = 0, tag = 0;
int index_, state_led, Time;
unsigned long pretime, thistime;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  String msg = "";
  int i=0;
  while (i<length) {
  msg += (char)payload[i++];
  }
  Serial.println(msg);
  spilt(msg);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "clientId-GQGghhOyDs"; //<--------------- clientId
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test_input", "connected_12"); //<------------------- topic publish
=======
      client.publish("test_input", "connected_10"); //<------------------- topic publish
      // ... and resubscribe
      client.subscribe("test_output"); //<--------------------- topic subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(D0, OUTPUT); //light 1
  pinMode(D1, OUTPUT); //light 2
  pinMode(D2, OUTPUT); //light 3
  pinMode(D5, INPUT); // lazor input
  pinMode(D6, OUTPUT); // buzzer
  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
}
int bonus = 0;

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(index_ == 12){               //<-----------------------Normal mode
      Serial.println("Start Index 12");
  if(index_ == 10){               //<-----------------------Normal mode
      Serial.println("Start Index 10");
      if(state_led == 1){
        game(1);
      }
      else if((bonus==1)&&(state_led == 2)){
        game_bonus();
      }
      else if(state_led == 2){
        game(2);
      }
  }
  else if(Time == 9999){
    bonus = 0;
    Serial.println("End Bonus");
    digitalWrite(D2, 0);
    tone(D6, NOTE_G4);
    delay(2000);
    digitalWrite(D2, 1);
    tone(D6, 0);
    index_ = 0;
    state_led = 0;
    Time = 0;
  }
  else if(index_ == 99){           //<-----------------------Bonus time mode
    Serial.println("Start Bonus");
    digitalWrite(D0, 0);
    tone(D6, NOTE_G4);
    delay(2000);
    digitalWrite(D0, 1);
    tone(D6, 0);
    bonus = 1;
    index_ = 0;
    state_led = 0;
    Time = 0;
  }
}

void led(int num){
  if(num == 1){
    digitalWrite(D0, 0);
  }
  else if(num == 2){
    digitalWrite(D1, 0);
  }
}


void game_bonus(){
  Serial.println("Game Bonus");
  tone(D6, NOTE_G4);
  delay(100);
  tone(D6, 0);
  pretime = millis();
  while(true){
     led(state_led);
     delay(1);
     thistime = millis();
     if(thistime-pretime >= Time){
       digitalWrite(D1, 1);
       client.publish("test_input", "0");
       break;
     }
     else if(digitalRead(D5) == 1){
       digitalWrite(D1, 1);
       audio();
       Serial.println("---Hit---");
       client.publish("test_input", "2");
       break;
     }
  }
  index_ = 0;
  state_led = 0;
  Time = 0;
}

void game(int point){
  String point_str = String(point);
  char point_chr[2]; 
  tone(D6, NOTE_G4);
  delay(100);
  tone(D6, 0);
  led(point);
  pretime = millis();
  while(true){
    delay(1);
    thistime = millis();
    if(thistime-pretime >= Time){
      digitalWrite(D0, 1);
      digitalWrite(D1, 1);
      client.publish("test_input", "-1");
      break;
    }
    else if(digitalRead(D5) == 1){
      digitalWrite(D0, 1);
      digitalWrite(D1, 1);
      audio();
      Serial.println("---Hit---");
      point_str.toCharArray(point_chr, 2);
      client.publish("test_input", point_chr);
      break;
    }
  }
  index_ = 0;
  state_led = 0;
  Time = 0;
}

void audio(){
  tone(D6, NOTE_A4);
  delay(100);
  tone(D6, 0);
  delay(100);
  tone(D6, NOTE_A4);
  delay(100);
  tone(D6, 0);
}

void spilt(String txt){
  String txt2, txt3, txt4;
  txt2 = txt.substring(0, 2);
  txt3 = txt.substring(3, 5);
  txt4 = txt.substring(6);
  index_ = txt2.toInt();
  state_led = txt3.toInt();
  Time = txt4.toInt();
  Serial.println(index_);
  Serial.println(state_led);
  Serial.println(Time);
}
