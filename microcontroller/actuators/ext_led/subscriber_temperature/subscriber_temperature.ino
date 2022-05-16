#include "MqttClient.h"
#include "WifiClient.h"
#include <ArduinoJson.h>

#define LED D1 //green external LED connected to NodeMCU's pin GPIO5 (D1)
//#define LED 13 //external LED connected to WeMos's pin GPIO14

String ssid_wifi = "netw0";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char *mqtt_broker_ip = "192.168.1.3";
const int mqtt_broker_port = 1883;
const char *client_id = "subscriber_DHT11";
const int num_subscribe_topics = 1;
String subscribe_topics[num_subscribe_topics] = {"temperature_topic"};
WifiClient wifi_client(ssid_wifi, pass_wifi);
MqttClient mqtt_client(mqtt_broker_ip, mqtt_broker_port, subscribe_topics, num_subscribe_topics);

float temperature = 0;
float humidity = 0;
float blink_delay = 100;

void setup(){
  Serial.begin(115200); // establish serial communication at baud rate 115200
  wifi_client.connect();
  mqtt_client.connect(client_id);
  pinMode(LED, OUTPUT); // initialize LED as an output
}

void loop(){
  mqtt_client.check_connection(client_id);
  String msg = mqtt_client.get_msg();
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, msg);
  temperature = doc["temperature"];
  if (temperature >= 10.0 && temperature < 20.0){
    blink_delay = 2000;
  }
  else if (temperature >= 20.0 && temperature < 30.0 ){
    blink_delay = 500;
  }
  else{
    blink_delay = 1000;
  }
  digitalWrite(LED, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(blink_delay);      // wait
  digitalWrite(LED, LOW);  // turn the LED off by making the voltage LOW
  delay(blink_delay);      // wait
}
