#include <Edspert_sht20.h>
#include <Edspert_soil_moisture.h>

HardwareSerial serial(1);

#define D_PIN 32
#define A_PIN 35
#define A_PIN_WL 33

Edspert_soil_moisture sm(D_PIN, A_PIN);
Edspert_soil_moisture wl(A_PIN_WL);
Edspert_sht20 sht20(&serial, 9600, 16, 17);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sm.begin();
  sht20.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("=====================");
  Serial.printf("soil moisture : %d\n", sm.readDigital());
  Serial.printf("soil moisture : %d\n", sm.readRaw());
  Serial.printf("water level   : %d\n", wl.readRaw());
  Serial.printf("Temperature   : %.2f^C\n", sht20.readTemperature());
  Serial.printf("Humidity      : %.2fRH\n", sht20.readHumidity());
  Serial.println("=====================");

  delay(1000);
}

