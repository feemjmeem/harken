#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

char message[] = "A test message from a feem";
char message2[] = "Another test message from a feem";
char titlemessage[] = "Now Playing [Spotify]";
int x, minXa, minXb;

void advanceframe() {
    display.clearDisplay();
    display.setCursor(0,7);
    display.setTextSize(1);
    display.print(titlemessage);
    display.setTextSize(2);
    display.setCursor(x, 20);
    display.print(message);
    display.setCursor(x, 35);
    display.print(message2);
    display.display();
    x = x - 1;
    if(x < minXa && x < minXb) x = display.width();
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  display.setTextWrap(false);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  x = display.width();
  minXa = -12 * strlen(message);
  minXb = -12 * strlen(message2);
}

void loop() {
    advanceframe();
}