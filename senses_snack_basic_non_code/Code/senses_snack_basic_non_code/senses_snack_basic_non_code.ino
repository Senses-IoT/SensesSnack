#include "parameter.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#include "Senses_wifi_esp32.h"
#include "DHT.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 14
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
String response_dht22;
float t, h;

#define led_pin 13
int control_port = 1;
bool current_state = false;
bool last_state = false;
String response_led;

int interval_upload = 10;


Senses_wifi_esp32 myiot;

void setup() {
  Serial.begin(115200);
  Serial.println("Hello ");

  EEPROM.begin(512);
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);



  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  setup_wifi();


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

  response_dht22 = myiot.connect(ssid, passw, userid, key);
  Serial.println(response_dht22);

  delay(2000);
  display.clearDisplay();


  Serial.println("Ready !!");

}

void loop()
{
  fn_ping();
  response_dht22 = "";
 

  response_led = myiot.getDigitalControl(control_port); 

  if (response_led == "on" )
  {
    current_state = true;
    if (current_state != last_state)
    {
      Serial.println(response_led); 
      last_state = true;
    }
  }

  if (response_led == "off" )
  {
    current_state = false;
    if (current_state != last_state)
    {
      Serial.println(response_led); 
      last_state = false;
    }
  }

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    cnt_step ++;
  }

  if (cnt_step >= 2)
  {
    display.setTextSize(1);
    display.setCursor(24, 50);
    display.print("DHT reading..");
    display.display();
    delay(1000);
    display.setTextColor(BLACK);
    display.setCursor(24, 50);
    display.print("DHT reading..");
    display.display();

    display.setTextColor(WHITE);

    /* - DHT sensor reading - */
    t = dht.readTemperature();
    h = dht.readHumidity();

    if (isnan(t) || isnan(h)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }

  if (cnt_step >= 3)
  {

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(5, 10);
    display.print("T " + String(t));

    display.setTextSize(1);
    display.print(" C");

    display.setTextSize(2);
    display.setCursor(5, 30);
    display.print("H " + String(h));

    display.setTextSize(1);
    display.print(" % RH");

    display.display();

    Serial.println("Temperature is " + String(t) + " celcuis");
    Serial.println("Humidity is " + String(h) + " %RH");
    Serial.println("----------------------------------------");

  }

  if (cnt_step >= interval_upload+3 && cnt_step <= interval_upload+3)
  {

    Serial.println("Sending data to SENSES IoT platform..");

    display.setTextSize(1);
    display.setCursor(0, 50);
    display.print("Updating Dashboard..");
    display.display();

    response_dht22 = myiot.send(1, t);
    Serial.println(response_dht22);

    response_dht22 = myiot.send(2, h);
    Serial.println(response_dht22);

  }

  if (cnt_step >= interval_upload+4)
  {

    display.setTextColor(BLACK);
    display.setCursor(0, 50);
    display.print("Updating Dashboard..");
    display.display();

    display.setTextColor(WHITE);

    cnt_step = 0;
  }

}
