#include "mqtt.h"
#include <ArduinoJson.h>
#include "credentials.h"
#include <WiFi.h>

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient); 

//used to setup MQTT server and callback function
void mqtt_setup() {

  //Set server and port for MQTT broker
  mqttClient.setServer(mqttServer, mqttPort);

  // set the callback function
  mqttClient.setCallback(mqtt_callback);
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

//mqtt_callback function is called when a message is received
void mqtt_callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Callback occured\n");
  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.print("\n");

  if(topic==MASTER_UPDATES_TOPIC)
  {
    //Parse updates 
    parse_mqtt_updates(payload);
  }
  else if(topic==SLAVE_UPDATES_TOPIC)
  {
    //parse updates from slaves 

    //check with the desired state present in the master 
  }
}

void mqtt_publish_signal(int green_slave, int timer_in_s)
{
  char payload[500];
  // sprintf(payload, "{\"green\":%d,\"timer\":%d}", green_slave, timer_in_s);
  // mqttClient.publish(SIGNAL_PUBLISH_TOPIC, payload);

  const int capacity = JSON_OBJECT_SIZE(3);
  StaticJsonBuffer<capacity> jb;

  // Create a JsonObject
  JsonObject& obj = jb.createObject();  

  obj["green"]=green_slave;
  obj["timer"]=timer_in_s;

  //Serializing into payload 
  obj.printTo(payload);

  mqttClient.publish(SIGNAL_PUBLISH_TOPIC, payload);

}

void parse_mqtt_updates(byte* payload)
{
  Serial.print("Starting to parse updates on master...\n");

  //compute capacity 
  const int capacity = JSON_OBJECT_SIZE(9);

  DynamicJsonBuffer jb(capacity);                           //Memory pool
  JsonObject& parsed = jb.parseObject(payload); //Parse message

  if(!parsed.success())
  {
    Serial.println("Parsing failed");
    delay(5000);
    return;
  }
  
  //Get the data here
  int clients = parsed["clients"];
  const char* sender = parsed["sender"];
  int timers[clients];                    //time in seconds

  //Update timers
  for(unsigned int i=0; i<clients; i++)
  {
    char* clientname="timer";
    clientname += (i+1);
    timers[i] = parsed[clientname];
  }

  //Pass the timers as limits in the delay_set function 
}