#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

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

  randomSeed(micros());

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
  //int val = msg.toInt();
  //digitalWrite(D0,val);

 
  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is active low on the ESP-01)
  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

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
      client.publish("test_input", "connected"); //<------------------- topic publish
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
  pinMode(D6, OUTPUT);
  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
}


void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  if(index_ == 3){
      if(state_led == 1){
        Game(1);
        index_ = 0;
      }
      else if(state_led == 2){
        Game(2);
      }
  }
   index_ = 0;
}

void led(int num){
  if(num ==1)
    digitalWrite(D0, 1);
  else
    digitalWrite(D1, 1);
}

void Game(int num_i){
  digitalWrite(D6, 1);
  delay(100);
  digitalWrite(D6, 0);
  if(num_i == 1)
    digitalWrite(D0, 0);
  else
    digitalWrite(D1, 0);
  char num_c[3];
  String num_s = String(num_i);
  pretime = millis();
  while(true){
    delay(1);
    thistime = millis();
    if(thistime-pretime>=Time){
      led(num_i);
      client.publish("test_input", "-1");
      break;
    }
    else if(digitalRead(D5)==1){
      led(num_i);
      Serial.print("------->Hit");
      num_s.toCharArray(num_c, 3);
      client.publish("test_input", num_c);
      break;
    }
  }
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
