#include "mqtt_client.h"
#include "wifi_connection.h"
#include <ArduinoJson.h>

#define LED D1 //green external LED connected to NodeMCU's pin GPIO5 (D1)
//#define LED 13 //external LED connected to WeMos's pin GPIO14

String ssid_wifi = "netw0";     // student's network SSID
String pass_wifi = "password1"; // student's network password

const char* mqtt_broker_ip = "192.168.1.3"; // broker IP address
const int mqtt_broker_port = 1883; // MQTT port 
const char* client_id = "subscriber_DHT11";
char* mqtt_topic = "temperature_topic";

float temperature = 0;
float humidity = 0;
float blink_delay = 100;

void setup(){
  Serial.begin(115200); // establish serial communication at baud rate 115200
  connect_to_wifi(ssid_wifi, pass_wifi);
  initialize_client(mqtt_broker_ip, mqtt_broker_port);
  connect(client_id);
  subscribe_to_topic(mqtt_topic);
  pinMode(LED, OUTPUT); // initialize LED as an output
}

void loop(){
  check_connection(client_id);
  String msg = get_msg();
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, msg);
  temperature = doc["temperature"];
  Serial.println(temperature);
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
