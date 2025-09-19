
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c 

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64 
#define OLED_RESET -1   

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); 

const int pinLM35 = A0; 
const unsigned long intervalo = 1000; 
unsigned long ultimaMillis = 0;

void setup()   {
  Serial.begin(9600);
  
  delay(250); 
  display.begin(i2c_Address, true); 
  display.setContrast (255); 
 
  display.clearDisplay();
  display.display();

}

void loop() {
  display.setTextSize(1); 
  display.setTextColor(SH110X_WHITE); 
  display.setCursor(1, 0);
  display.println("LM35 - Lectura simple");
  display.setCursor(10, 11);
  display.println("Temperatura: ");
  unsigned long ahora = millis();
  if (ahora - ultimaMillis >= intervalo) {
    ultimaMillis = ahora;

    int lectura = analogRead(pinLM35);              
    const float Vref = 5.0;                         
    float voltaje = lectura * (Vref / 1023.0);      
    float tempC = voltaje * 100.0;                  
  display.setCursor(11,22);
  display.println(tempC, 2);
  }

  display.display();
  delay(5000);
  display.clearDisplay();
}