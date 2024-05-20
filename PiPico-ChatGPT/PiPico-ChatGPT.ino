#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define LED_PIN       LED_BUILTIN

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char* ssid = "AP-Taller";
const char* password = "Ccomputo0908";
const char* openaiApiKey = "sk-proj-YzNwV4jR8kLpZxQ6MdG2HsBxPfC7YrJ8AbT3FvUiK9QxW5En";

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Toggle LED to show connection attempt
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  digitalWrite(LED_PIN, LOW); // Turn off LED when connected
  Serial.println("Connected to WiFi");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin("https://api.openai.com/v1/engines/davinci-codex/completions");
    http.addHeader("Content-Type", "application/json");
    http.addHeader("Authorization", String("Bearer ") + openaiApiKey);
    
    String payload = "{\"prompt\":\"¿Cuéntame un chiste?\",\"max_tokens\":60,\"temperature\":0.5,\"n\":1,\"stop\":\"\\n\"}";
    
    int httpResponseCode = http.POST(payload);
    
    if (httpResponseCode == HTTP_CODE_OK) {
      String response = http.getString();
      int start = response.indexOf("\"text\":\"") + 8;
      int end = response.indexOf("\",\"index\"");
      String answer = response.substring(start, end);
      
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE);
      display.setCursor(0, 0);
      display.println(answer);
      display.display();
    } else {
      Serial.println("HTTP request failed");
    }
    
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
  
  delay(10000); // Wait for 10 seconds before making another request
}

}