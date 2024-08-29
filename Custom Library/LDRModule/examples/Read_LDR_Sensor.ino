//------------------------------//
// Author      : sonson
// Date        : 21-07-2024
// Description : This program is used to read the LDR sensor using a custom library.
//------------------------------//

#include "LDR.h"

#define pinLDR 13
LDR ldr(pinLDR);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  ldr.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  float dataLux = ldr.readIntensitas();
  // float dataLux2 = ldr.readIntensitas(2);
  bool statusLDR = ldr.readStatus(500);

  Serial.print("  Nilai Lux ");
  Serial.print(dataLux);
  // Serial.print("  Nilai KLux ");
  // Serial.print(dataLux2);

  if (statusLDR == 1){
    Serial.print("  State Gelap");
  }
  else{
    Serial.print("  State Terang");
  }
  delay(500); // this speeds up the simulation
}





