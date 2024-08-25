// Penulis   : Ahmad Sony Alfathani
// Versi 	  : V.1.2
// Tanggal   : 14 Desember 2023
// Deskripsi :Library versi ini adalah library yang digunakan untuk membuat ESp32 sebagai Publisher dan Subscriber

#ifndef EDSPERTPUBSUB_H
#define EDSPERTPUBSUB_H

#include <Arduino.h>

class EdspertPubSub{

  public:
    void connect_to_AP(char* mySSID, char* myPASS);
    void init_to_broker(char* myMqttServer, int myMqttPort);
    void connect_to_broker(String clientName, String userMQTT = "", String passwordMQTT= "");
    void mqtt_publish(String yourTopic, String yourPayload);
    void mqtt_subscribe(String yourTopic);
    int statusConnection();
    void rxMessFrBroker();

};



#endif
