
#include "FirebaseESP8266.h"
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "iiot-5f66d.firebaseio.com/User%201" //Without http:// or https:// schemes
#define FIREBASE_AUTH "iaxxK0KD4kq0SJRnbjIjWBwRBvXNlB0kEuhnblfK"
#define WIFI_SSID "tech rick iot"
#define WIFI_PASSWORD "techrick"

//Define FirebaseESP8266 data object
FirebaseData firebaseData;


unsigned long sendDataPrevMillis = 0;

String path = "led1_state";

uint16_t count = 0;

void printResult(FirebaseData &data);

void setup()
{

  Serial.begin(115200);
 pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  //Set the size of WiFi rx/tx buffers in the case where we want to work with large data.
  firebaseData.setBSSLBufferSize(1024, 1024);

  //Set the size of HTTP response buffers in the case where we want to work with large data.
  firebaseData.setResponseSize(1024);

  if (!Firebase.beginStream(firebaseData, path))
  {
    Serial.println("------------------------------------");
    Serial.println("Can't begin stream connection...");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}

void loop()
{

 Serial.println(firebaseData.stringData());
if (Firebase.getString(firebaseData, path)) {

    if (firebaseData.stringData()== "1") {
         Serial.println(firebaseData.stringData());
       digitalWrite(LED_BUILTIN,HIGH);
        Serial.println("ON");
      delay(100);
    }
 
    if (firebaseData.stringData()== "0") {
         Serial.println(firebaseData.stringData());
       digitalWrite(LED_BUILTIN,LOW);
        Serial.println("OFF");
      delay(100);
    }
    

  } else {
    Serial.println(firebaseData.errorReason());
  }
}
