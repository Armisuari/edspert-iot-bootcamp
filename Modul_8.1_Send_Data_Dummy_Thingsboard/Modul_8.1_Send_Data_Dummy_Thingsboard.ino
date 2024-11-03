#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

// Parameter Wi-Fi 
String ssid = "Wokwi-GUEST";
String password = "";

// Parameter URL/Endpoint 
String accessToken = "thingsboard-access-token";
String url = "https://demo.thingsboard.io/api/v1/"+ accessToken + "/telemetry";

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);
  Serial.println();

  // Initialize Wi-Fi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void loop() {
 WiFiClientSecure *client = new WiFiClientSecure;
  if(client) {
    // set secure client without certificate
    client->setInsecure();
    //create an HTTPClient instance
    HTTPClient https;

    //Initializing an HTTPS communication using the secure client
    Serial.print("[HTTPS] begin...\n");
    
    https.begin(*client, url);
    String httpsBody = "{\"temperature\":25.1, \"humidity\":70}";
    int httpsResponseCode = https.POST(httpsBody);

    Serial.print("HTTPS Response Code: ");
    Serial.println(httpsResponseCode);

    https.end();
    delay(20000);
  }
}