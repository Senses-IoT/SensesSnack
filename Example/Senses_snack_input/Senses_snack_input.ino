#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "Senses_wifi_esp32.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define BUTTON 13
#define ADC 35

int adc = 0;
int button = 0;

const char *ssid = "BiG";
const char *passw = "12123121210";
const char *userid = "122";
const char *key = "p3itsvhtzzj7";

String response;

Senses_wifi_esp32 myiot;

void setup() {

  Serial.begin(9600);
  pinMode(BUTTON, INPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);

  display.setTextSize(2);
  display.setCursor(32, 10);
  display.println("SENSES");

  display.setTextSize(1);
  display.setCursor(32, 26);
  display.println("IoT platform");

  display.setCursor(12, 40);
  display.println("with Senses SNACK !");

  display.setCursor(32, 54);
  display.println("starting...");

  display.display();

    response = myiot.connect(ssid, passw, userid, key);
    Serial.println(response);

  delay(2000);
  display.clearDisplay();

}

void loop() {

  response = "";
  adc = analogRead(ADC);
  button = digitalRead(BUTTON);

  display.setTextSize(1);
  display.setCursor(24, 50);
  display.print("Sensor reading..");
  display.display();
  delay(500);
  display.setTextColor(BLACK);
  display.setCursor(24, 50);
  display.print("Sensor reading..");
  display.display();

  display.setTextColor(WHITE);
  delay(500);

  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(1, 5);
  if (button == 1) {
    display.print("BTN: 1");
  }
  else{
    display.print("BTN: 0");
  }


  display.setTextSize(2);
  display.setCursor(1, 30);
  display.print("ADC: " + String(adc));

  display.display();

  Serial.println("Sending data to SENSES IoT platform..");
  Serial.println("Button is " + String(button));
  Serial.println("ADC    is " + String(adc));
  Serial.println("----------------------------------------");

  display.setTextSize(1);
  display.setCursor(0, 50);
  display.print("Updating Dashboard..");
  display.display();

    response = myiot.send(1, button);
    Serial.println(response);
  
    response = myiot.send(2, adc);
    Serial.println(response);

  delay(500);

  display.setTextColor(BLACK);
  display.setCursor(0, 50);
  display.print("Updating Dashboard..");
  display.display();

  display.setTextColor(WHITE);
}
