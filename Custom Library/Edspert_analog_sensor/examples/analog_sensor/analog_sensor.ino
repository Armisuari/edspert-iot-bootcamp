#include <Edspert_soil_moisture.h>

#define D_PIN 32
#define A_PIN 35
#define A_PIN_WL 33

Edspert_soil_moisture sm(D_PIN, A_PIN);
Edspert_soil_moisture wl(A_PIN_WL);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sm.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("soil moisture : %d\n", sm.readDigital());
  Serial.printf("soil moisture : %d\n", sm.readRaw());
  Serial.printf("water level   : %d\n", wl.readRaw());
  delay(1000);
}

