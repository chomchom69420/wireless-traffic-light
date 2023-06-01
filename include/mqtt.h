#include <PubSubClient.h>
#include "credentials.h"
#include <WiFi.h>

//used to setup MQTT server and callback function
void setupMQTT();

//for connecting to MQTT broker
void reconnect();

//callback function is called when a message is received
void callback(char* topic, byte* payload, unsigned int length);