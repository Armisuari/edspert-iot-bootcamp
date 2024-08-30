#include <ArduinoJson.h>
#include <StreamUtils.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define pinLED 23

const char* ssid = ""; // isikan dengan SSID wifi Anda. SSID Wokwi "Wokwi-GUEST"
const char* password = ""; // isikan dengan password wifi Anda. Password SSID Wokwi tanpa Password biarkan ""
const String appName = ""; // isikan dengan nama application antares Anda
const String devName = ""; // isikan dengan nama device antares Anda
const String accessKey = ""; // isikan dengan access key antares Anda
const String url = String("http://platform.antares.id:8080/~/antares-cse/antares-id/"+ appName+"/"+devName+"/la");

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(pinLED, OUTPUT);
}

void loop() {
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("OK! IP=");
  Serial.println(WiFi.localIP());

  Serial.print("Fetching " + url + "... ");

  HTTPClient http;
  http.begin(url);
  http.addHeader("X-M2M-Origin", accessKey);
  http.addHeader("Content-Type", "application/json;ty=4");
  http.addHeader("Accept", "application/json");
  
  http.GET();
  
  DynamicJsonDocument doc(1024);
  DynamicJsonDocument content(1024);

  ReadLoggingStream loggingStream(http.getStream(), Serial);
  deserializeJson(doc, loggingStream);

  String con = doc["m2m:cin"]["con"];
  deserializeJson(content, con);
  
  int status = content["status"];
  Serial.println();
  Serial.println();
  Serial.print("status led dari antares: ");
  Serial.println(status);  
  
  if(status == 1){
    Serial.println("status 1");
    digitalWrite(pinLED, HIGH);
  } else {
    Serial.println("status 0");
    digitalWrite(pinLED, LOW);
  }
  
  Serial.println();
  delay(5000);
}
