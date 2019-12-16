#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

const char* ssid = "lab_startup";
const char* password = "56841725";
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
    String clientId = "clientId-1LxJrpxOSx"; //<--------------- clientId
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("hall_input", "connected_hall"); //<------------------- topic publish
      // ... and resubscribe
      client.subscribe("hall_output"); //<--------------------- topic subscribe
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
  pinMode(D3, INPUT); // lazor input
  pinMode(D5, INPUT); // lazor input
  pinMode(D7, INPUT); // lazor input
  pinMode(D6, OUTPUT); // buzzer
  digitalWrite(D0, 0);
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(index_ == 1){
    Serial.println("index 1");
    digitalWrite(D0, 1);
    game();
  }
  else if(index_ == 2){
    Serial.println("index 2");
    digitalWrite(D1, 1);
    game();
  }
  else if(index_ == 3){
    Serial.println("index 3");
    digitalWrite(D2, 1);
    game();
  }
}

void game(){
  tone(D6, NOTE_G4);
  delay(100);
  tone(D6, 0);
  pretime = millis();
  while(true){
    delay(1);
    thistime = millis();
    if(thistime-pretime >= Time){
      setzero();
      client.publish("hall_input", "-1");
      break;
    }
    else if(digitalRead(D3) == 1){
      turn_light();
      audio();
      Serial.println("Hit");
      client.publish("hall_input", "1");
      break;
    }
    else if(digitalRead(D7) == 1){
      turn_light();
      audio();
      Serial.println("Hit");
      client.publish("hall_input", "1");
      break;
    }
    else if(digitalRead(D5) == 1){
      turn_light();
      audio();
      Serial.println("Hit");
      client.publish("hall_input", "1");
      break;
    }
  }
  setzero();
}

void setzero(){
  index_ = 0;
  state_led = 0;
  Time = 0;
}

void  turn_light(){
  digitalWrite(D0, 0);
  digitalWrite(D1, 0);
  digitalWrite(D2, 0);
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
