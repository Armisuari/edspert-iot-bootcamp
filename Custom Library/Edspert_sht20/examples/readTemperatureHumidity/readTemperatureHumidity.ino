#include <Edspert_sht20.h>

HardwareSerial serial(1);

Edspert_sht20 sht20(&serial, 9600, 16, 17);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  sht20.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.printf("Temperature: %.2f^C\n Humidity: %.2fRH\n", sht20.readTemperature(), sht20.readHumidity());

  delay(1000);
}