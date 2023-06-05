#include <PubSubClient.h>

#define SLAVE_UPDATES_TOPIC "/traffic/slave_updates"
#define MASTER_UPDATES_TOPIC "/traffic/updates"
#define SIGNAL_PUBLISH_TOPIC "/traffic/signals"

//used to setup MQTT server and callback function
void mqtt_setup();

//for connecting to MQTT broker
void reconnect();

//callback function is called when a message is received
void mqtt_callback(char* topic, byte* payload, unsigned int length);

void mqtt_publish(char* topic, char* payload);