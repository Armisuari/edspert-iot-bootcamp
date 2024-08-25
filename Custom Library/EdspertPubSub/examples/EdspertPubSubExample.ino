//------------------------------//
// Author      : sonson
// Date        : 21-07-2024
// Description : This program is used to publish & subscribe with MQTT protocol using a custom library.
//------------------------------//
#include "EdspertPubSub.h"
#include <DHT.h>              // Library DHT
#include <ArduinoJson.h>      // https://arduinojson.org/v6/example/

// Wifi Setting
char* ssid = "Wokwi-GUEST";
char* password = "";

// MQTT Setting
char *mqttServer = "broker.emqx.io";
int mqttPort = 1883;
String myClientID = "001";
String ourTopic = "edspert/data";
EdspertPubSub clientMQTT;


// Define Sensor 
#define DHTPIN 19            // Pin DHT
#define DHTTYPE DHT22         // Type DHT
DHT dht(DHTPIN, DHTTYPE);     // Membuat DHT objek disebut "dht"pada pin dan dengan jenis sensor DHT

StaticJsonDocument<200> doc;
String jsonString;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("ESP Connect to AP");
  clientMQTT.connect_to_AP(ssid, password);
  clientMQTT.init_to_broker(mqttServer,mqttPort); // setup koneksi ke broker
}

void loop() {
  //Memastikan koneksi ke MQTT
    clientMQTT.connect_to_broker(myClientID);   // Try to connect with broker
    // Read Data
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();

    // // Tambahkan data "temp" ke objek JSON
    doc["temp"] = temperature;
    doc["hum"] = humidity;

    // // Serializasikan objek JSON ke dalam string JSON
    jsonString = "";    // Riset Payload JsonString
    serializeJson(doc, jsonString);

    // Publish Data hanya satu data JSon
    clientMQTT.mqtt_publish(ourTopic,jsonString);

    delay(5000);

}