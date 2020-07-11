#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Wire.h>
#include "config.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char *ssid = WIFI_SSID;
const char *password = WIFI_PASSWORD;
const char *topbar = "Now Playing [Spotify]";
const char *artist = "Bagel Man";
const char *title = "Meatball Sandwich Time";

int xa, xb, minXa, minXb;

void advanceframe() {
    display.clearDisplay();
    display.setCursor(0,7);
    display.setTextSize(1);
    display.print(topbar);
    display.setTextSize(2);
    display.setCursor(xa, 20);
    display.print(artist);
    display.setCursor(xb, 35);
    display.print(title);
    display.display();
    xa = xa - 1;
    xb = xb - 1;
    if (xa < minXa) {
        xa = display.width();
    }
    if (xb < minXb) {
        xb = display.width();
    }
}

void updatemessagelength() {
    minXa = -12 * strlen(artist);
    minXb = -12 * strlen(title);
}

void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextWrap(false);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  xa = display.width();
  xb = display.width();
  updatemessagelength();

  Serial.printf("\nConnecting...");

}

void loop() {
    advanceframe();
}