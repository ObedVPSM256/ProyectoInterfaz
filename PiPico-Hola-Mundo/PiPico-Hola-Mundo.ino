#include <Arduino.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Hola, Raspberry Pi Pico W!");
}
void loop() {
while(Serial.available() > 0){

String cadena = Serial.readStringUntil('\n');
cadena = cadena.substring(0,cadena.length());
Serial.println(cadena);
}
  delay(1000);
}

