// Penulis   : Ahmad Sony Alfathani
// Versi    : V.1.2
// Tanggal   : 14 Desember 2023
// Deskripsi :Library versi ini adalah library yang digunakan untuk membuat ESp32 sebagai Publisher dan Subscriber

#include "EdspertPubSub.h"
#include <WiFi.h>
#include <PubSubClient.h>     // Library untuk mengkoneksikan ESP32 ke MQTT broker


WiFiClient wifiClient;                // Membuat objek wifiClient
PubSubClient mqttClient(wifiClient);  // Membuat  objek mqttClient dengan konstruktor objek WiFiClient (Permintaan dari Lib)

String callBackPayload;
String callBackTopic;

// Fungsi untuk Mengkoneksikan ESP32 ke AP
void EdspertPubSub::connect_to_AP(char* mySSID, char* myPASS){
  WiFi.mode(WIFI_STA);
  WiFi.begin(mySSID, myPASS);   // Mencoba connect ke Wifi
  // Melakukan pengecekan terhadap status koneksi ke WI-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } 
  Serial.println("");
  Serial.print("Device telah terhubung ke: ");
  Serial.println(mySSID);
  Serial.print("IP Device: ");
  Serial.println(WiFi.localIP());
}


// --------- Di aktifkan jika ingin sebagai Subscriber ---------//
//  fungsi yang akan dipanggil ketika klien menerima pesan dari broker 
//  MQTT yang sesuai dengan langganan yang telah dibuat sebelumnya. 
void callback(char* topic, byte* message, unsigned int length) {
  // Serial.print("Callback - ");
  // Serial.print("Message:");
  String stMessage;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    stMessage += (char)message[i];
  }

  callBackPayload = stMessage;
  callBackTopic = topic;
}


// mengatur dan menginisialisasi koneksi ke broker MQTT 
// serta menetapkan fungsi callback yang akan dipanggil 
// ketika pesan diterima oleh klien dari langganan yang dibuat.
void EdspertPubSub::init_to_broker(char* myMqttServer, int myMqttPort) {
  mqttClient.setServer(myMqttServer, myMqttPort); // Mengatur detail broker target  yang digunakan
  // jika kita ingin menerima pesan untuk langganan yang dibuat oleh klien sebagai subscriber
  mqttClient.setCallback(callback);           
}

void EdspertPubSub::rxMessFrBroker(){
  mqttClient.loop();
}

// untuk melakukan koneksi ulang (reconnect) ke broker MQTT 
// jika klien kehilangan koneksi dengan broker 
// atau gagal melakukan koneksi saat pertama kali menjalankan program.
// ESP32 Reconnect to broker
void EdspertPubSub::connect_to_broker(String clientName, String userMQTT, String passwordMQTT) {
  if (!mqttClient.connected()){
    Serial.println("Connecting to MQTT Broker...");
    String clientId = "ESP32Client-" + clientName;
    mqttClient.connect(clientId.c_str(), userMQTT.c_str(), passwordMQTT.c_str());
    while (!mqttClient.connected()) {
        Serial.print("failed, rc=");
        Serial.println(mqttClient.state());
        Serial.println("Reconnecting to MQTT Broker..");
        delay(1000);  
    }
    Serial.print(clientId);
    Serial.println(" Device to Broker Connected.");
  }
  else{
    
  }
}

int EdspertPubSub::statusConnection(){
  int statusConnectionToBroker = mqttClient.connected();
  return statusConnectionToBroker;
}

// Publish untuk Tipe data JSon dengan inputan Payload Float
void EdspertPubSub::mqtt_publish(String yourTopic, String yourPayload){
  
  mqttClient.publish(yourTopic.c_str(), yourPayload.c_str());
  Serial.print(yourTopic);
  Serial.print(" ==> ");
  Serial.println(yourPayload);
  // Serial.println(jsonString);
}

void EdspertPubSub::mqtt_subscribe(String yourTopic){
  mqttClient.subscribe(yourTopic.c_str());
}
