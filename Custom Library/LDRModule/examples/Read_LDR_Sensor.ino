//------------------------------//
// Author      : sonson
// Date        : 21-07-2024
// Description : This program is used to read the LDR sensor using a custom library.
//------------------------------//

#include "LDRModule.h"

#define pinLDR 13

LDRModule ldr(pinLDR);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dataLDR = ldr.bacaADC();
  float dataLux = ldr.intensitas();
  float dataLux2 = ldr.intensitas(2);
  Serial.print("Nilai LDR ");
  Serial.print(dataLDR);
  Serial.print("  Nilai Lux ");
  Serial.print(dataLux);
  Serial.print("  Nilai KLux ");
  Serial.println(dataLux2);
  delay(10); // this speeds up the simulation
}





