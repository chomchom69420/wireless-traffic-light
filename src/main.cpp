#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char *SSID = "redmi";
const char *PWD = "sohamc621";

long last_time = 0;
char data[100];

// MQTT client
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

char *mqttServer = "broker.hivemq.com";
int mqttPort = 1883;

//connects to the WiFi access point 
void connectToWiFi() {
  Serial.print("Connecting to ");
 
  WiFi.begin(SSID, PWD);
  Serial.println(SSID);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.print("Connected.");
  
} 


//callback function is called when a message is received
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Callback - ");
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
}


//used to setup MQTT server and callback function
void setupMQTT() {
  mqttClient.setServer(mqttServer, mqttPort);
  // set the callback function
  mqttClient.setCallback(callback);
}


//timer ISR
void IRAM_ATTR onTimer(){
  digitalWrite(13, !digitalRead(13));
}



void setup() {
  Serial.begin(9600);
  
  connectToWiFi();

  setupMQTT();

  pinMode(13, OUTPUT);
}


//for connecting to MQTT broker
void reconnect() {
  Serial.println("Connecting to MQTT Broker...");
  while (!mqttClient.connected()) {
      Serial.println("Reconnecting to MQTT Broker..");
      String clientId = "ESP32Client-";
      clientId += String(random(0xffff), HEX);
      
      if (mqttClient.connect(clientId.c_str())) {
        Serial.println("Connected.");
        // subscribe to topic
        mqttClient.subscribe("/swa/commands");
      }
      
  }
}


void loop() {

  if (!mqttClient.connected())
    reconnect();

  mqttClient.loop();

  long now = millis();
  if (now - last_time > 60000) {
    // Publishing data throgh MQTT
    sprintf(data, "%f", 220);
    mqttClient.publish("/soham/data_topic", data);
    last_time = now;
  }

}