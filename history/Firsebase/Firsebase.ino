#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Config Firebase
#define FIREBASE_HOST "https://lazershotkmitl.firebaseio.com/"
#define FIREBASE_AUTH "WtyRAjhqskV3djoq92VaEXonzMTjri9pV0FKUxXH"

// Config connect WiFi
#define WIFI_SSID "ITFORGE_UFOx"
#define WIFI_PASSWORD "IBPokg36"

int i = 0;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
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
  Firebase.setInt("number", i);
  if (Firebase.failed()) {
      Serial.print("set /number failed:");
      Serial.println(Firebase.error());
      return;
  }
  Serial.print("set /number to ");
  Serial.println(Firebase.getInt("number"));
  
  i++;
  delay(500);
}
