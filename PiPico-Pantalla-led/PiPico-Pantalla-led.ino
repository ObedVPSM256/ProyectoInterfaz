#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // Ancho del OLED en píxeles
#define SCREEN_HEIGHT 64 // Altura del OLED en píxeles
#define OLED_RESET     -1 // Reset no es usado

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Wire.begin();
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Dirección I2C del display cambiada de 0x3C a 0x3D
    while(true); // Bucle infinito si el display no se inicializa correctamente
  }

  display.clearDisplay();
  display.setTextSize(2);             // Tamaño de texto cambiado de 1 a 2
  display.setTextColor(SSD1306_WHITE); // Color del texto
  display.setCursor(10,10);           // Posición inicial del texto cambiada de (0,0) a (10,10)
  display.println("Hola Arduino!");   // Texto cambiado de "Hola mundo!" a "Hola Arduino!"
  display.display();
}

void loop() {
  display.clearDisplay();
  display.setTextSize(2);             
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(10,10);             
  display.println("Hola Arduino!");   // Texto cambiado de "Hola mundo!" a "Hola Arduino!"
  display.display();
}

