#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Set these to run example.
const char* WIFI_SSID = "Lab330";
const char* WIFI_PASSWORD = "33333330";
const char* MQTT_SERVER = "broker.mqttdashboard.com";
int randomNum, num;
String message;
char txt[10];
char *token;
String myString[3];
//Thread* myThread = new Thread();
WiFiClient espClient;
PubSubClient client(espClient);
unsigned long Showtime, Thistime;

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(MQTT_SERVER, 1883);
  client.setCallback(callback);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D5, INPUT);
  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }else{
    Gameplay();
  }
  client.loop();
}

void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
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
  num = 0;
  while (num < length) {                //collect char from MQTT to string valiable->(message)
    message += (char)payload[num++];
  }
  Serial.println(message);
  split();
  message = "";
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "clientId-dtT2UtiqhK"; //<--------------- clientId
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("test_output", "connected_1"); //<------------------- topic publish
      // ... and resubscribe
      client.subscribe("test_input"); //<--------------------- topic subscribe
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void Gameplay() { // ฟังก์ชั่นแรก เปิดแค่ไฟตัวหลอดเดียว
  delay(300);
  Serial.println("Comein");
  if (myString[0] == "1") {
    Serial.println("Start");
    OpenLed();
    Showtime = millis();
    while (1) {
      delay(1);
      Thistime = millis();
      if (Thistime/1000 - Showtime/1000 >= 5) {
        CloseLed();
        break;
      } else if (digitalRead(D5) == 1) {
        CloseLed();
        client.publish("test_output", "1");
        break;
      }
    }
      myString[0] = "";
      myString[1] = "";
  }
  Serial.println("Leave");
}

void split() {
  //print message before split
  Serial.println();
  Serial.print("Starting : ");
  Serial.println(message);
  Serial.println();

  message.toCharArray(txt, 10);    //convert string to char array
  token = strtok(txt, ":");        //split string from ':' the first time
  myString[0] = token;             //store string after split to myString[]

  int num = 1;
  while (token != NULL) {         //loop split and store
    token = strtok(NULL, ":");
    myString[num] = token;
    num += 1;
  }

  //print show result
  for (int i = 0; i < 2; i++) {
    Serial.print("myString[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.println(myString[i]);
    Serial.println();
  }
}

void OpenLed() {
  if (myString[1] == "RED") {
    digitalWrite(D0, 0);
  } else if (myString[1] == "GREEN") {
    digitalWrite(D1, 0);
  } else if (myString[1] == "BLUE") {
    digitalWrite(D2, 0);
  }
}

void CloseLed() {
  digitalWrite(D0, 1);
  digitalWrite(D1, 1);
  digitalWrite(D2, 1);
}
