#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Set these to run example.
const char* WIFI_SSID = "la330";
const char* WIFI_PASSWORD = "33333330";
const char* mqtt_server = "broker.mqttdashboard.com";
int randomNum;
//Thread* myThread = new Thread();
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long Showtime, Thistime;

void setup() {
  Serial.begin(11520);
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
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(D0, OUTPUT);
  pinMode(D5, INPUT);
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "clientId-5eLfzY0Z69"; //<--------------- clientId
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test_input", "connected_1"); //<------------------- topic publish
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

void loop() {
if (!client.connected()) {
    reconnect();
  }
  client.loop();
 }


void Gameplay(){ // ฟังก์ชั่นแรก เปิดแค่ไฟตัวหลอดเดียว
    randomNum = random(1, 3); // สุ่มตัวเลข
    if(randomNum==1){ // ถ้าสุ่มได้เลข 1 จะทำ if นี้
      Showtime = millis();
      while(1){ // loop รันรอรับสัญญาณ เลเซอร์
          Thistime = millis();
          delay(1);
          analogWrite(D0, 255); // led เปิด
       if(Time(Thistime) == "Stop"){
          break;
       }else if(digitalRead(D5)==1){
        // ถ้าได้รับเลเซอร์ จะบวกคะแนน
        client.publish("test_input", "1");
        break;
      }
    }
      delay(1000); // เวลาหน่วงก่อนจะสุ่มใหม่
  }
}

String Time(unsigned long Showtime){
  Thistime = millis();
          delay(1);
       if(Thistime/1000-Showtime/1000>=1000){
          Serial.println(Thistime-Showtime/1000);
          Serial.println("Stop");
          return "Stop";
      }
}
