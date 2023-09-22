#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <PubSubClient.h>

#define FIREBASE_HOST "remote-health-monitor-b1a62-default-rtdb.firebaseio.com" //https://remote-health-monitor-b1a62-default-rtdb.firebaseio.com/
#define WIFISSID "ashraf754"                         // Put your WifiSSID here
#define PASSWORD "ashraf123"                         // Put your wifi password here
#define TOKEN "BBFF-cyPGOc5hADPAeRt5VvDXd96doGQpI8"  // Ashraf API code: "BBFF-Fa5BhZKZ0wnRUbCxBKrJm9WMSt3sqD"         // Put your Ubidots' TOKEN
#define MQTT_CLIENT_NAME "myecgsensor"               // MQTT client Name, please enter your own 8-12 alphanumeric character ASCII string;
#define FIREBASE_Authorization_key "9qlV5sXOfxTETB2dJuAuhS34yD0UlWFKKpjJJxtS"
FirebaseData firebaseData;
FirebaseJson json;

#define VARIABLE_LABEL "myecg"  // Assing the variable label
#define DEVICE_LABEL "esp8266"  // Assig the device label

#define SENSOR A0  // Set the A0 as SENSOR

char mqttBroker[] = "industrial.api.ubidots.com";
char payload[100];
char topic[150];
// Space to store values to send
char str_sensor[10];

WiFiClient ubidots;
PubSubClient client(ubidots);

void callback(char* topic, byte* payload, unsigned int length) {
  char p[length + 1];
  memcpy(p, payload, length);
  p[length] = NULL;
  Serial.write(payload, length);
  Serial.println(topic);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.println("Attempting MQTT connection...");

    // Attemp to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("Connected");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFISSID, PASSWORD);
  // Assign the pin as INPUT
  pinMode(SENSOR, INPUT);

  Serial.println();
  Serial.print("Waiting for WiFi...");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
  Firebase.begin(FIREBASE_HOST, FIREBASE_Authorization_key);

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  sprintf(topic, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
  sprintf(payload, "%s", "");                    // Cleans the payload
  sprintf(payload, "{\"%s\":", VARIABLE_LABEL);  // Adds the variable label

  float myecg = analogRead(SENSOR);

  /* 4 is mininum width, 2 is precision; float value is copied onto str_sensor*/
  dtostrf(myecg, 4, 2, str_sensor);

  sprintf(payload, "%s {\"value\": %s}}", payload, str_sensor);  // Adds the value
  Serial.println("Publishing data to Ubidots Cloud");
  Serial.println(myecg);
  client.publish(topic, payload);
  Firebase.setFloat(firebaseData, "ECG", myecg);
  client.loop();
}