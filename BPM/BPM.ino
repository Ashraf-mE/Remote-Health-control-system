#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>

#define FIREBASE_HOST "remote-health-monitor-b1a62-default-rtdb.firebaseio.com"
#define WIFI_SSID "ashraf754"  // Change the name of your WIFI
#define WIFI_PASSWORD "ashraf123"   // Change the password of your WIFI
#define FIREBASE_Authorization_key "9qlV5sXOfxTETB2dJuAuhS34yD0UlWFKKpjJJxtS"
FirebaseData firebaseData;
FirebaseJson json;

void setup() 
{
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting...");

  while (WiFi.status() != WL_CONNECTED) 
  {
    
    Serial.print(".");
    delay(300);
  }


  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);
}

void loop() {
  int bpm = analogRead(A0);
  int noise = 120;
  if (isnan(bpm))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  bpm = (bpm - noise)/10;
  Serial.print(" BPM: ");
  Serial.println(bpm);
  Firebase.setFloat(firebaseData, "BPM", bpm);
  delay(100);
}