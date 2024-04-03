int rev = 0;
const short int pinA = 4;

// for led
#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN_1 11
#define DATA_PIN_2 12
#include <Wire.h>     

float value = 0;
int rpm;
int rpmMax = 350;
int rpmVals[32];
CRGB colors[] = {
  CRGB(3, 161, 252),
CRGB(40, 158, 255),
CRGB(61, 155, 255),
CRGB(78, 152, 255),
CRGB(94, 148, 255),
CRGB(108, 144, 255),
CRGB(122, 140, 255),
CRGB(135, 136, 255),
CRGB(148, 131, 255),
CRGB(160, 125, 255),
CRGB(172, 119, 251),
CRGB(184, 113, 247),
CRGB(195, 106, 241),
CRGB(205, 99, 235),
CRGB(215, 91, 227),
CRGB(224, 82, 219),
CRGB(232, 73, 210),
CRGB(240, 62, 201),
CRGB(247, 50, 190),
CRGB(253, 35, 179),
CRGB(255, 10, 168),
CRGB(255, 0, 156),
CRGB(255, 0, 144),
CRGB(255, 0, 132),
CRGB(255, 0, 120),
CRGB(255, 0, 107),
CRGB(255, 0, 95),
CRGB(255, 0, 81),
CRGB(255, 0, 67),
CRGB(255, 0, 50),
CRGB(255, 0, 34),
CRGB(255, 12, 12)
};
CRGB ledsLeft[NUM_LEDS];
CRGB ledsRight[NUM_LEDS];

void setup() {
  pinMode(pinA, INPUT);
  Serial.begin(9600);

  // for led
  FastLED.addLeds<WS2812,DATA_PIN_1,RGB>(ledsLeft,NUM_LEDS);
  FastLED.addLeds<WS2812,DATA_PIN_2,RGB>(ledsRight,NUM_LEDS);
  FastLED.setBrightness(50);
  for (int i = 0; i < 32; i++) {
    rpmVals[i] = i * (rpmMax / 31);
  }
            
}

void loop() {
  unsigned long startTime = millis();
  unsigned long currTime = millis();
  rev = 0;
  static int last = 1;
  static int members = 5;

  while (currTime - startTime <= 1000) {
    int curr = digitalRead(pinA);
    if ((last == 1) && (curr == 0)) {
      rev++;
    }
    last = curr;
    Serial.println(rev);

    currTime = millis();
  }

  rpm = rev * 60 / members;
  Serial.println(rpm);
  for (int row = 0; row < 32; row++) {
    int row2 = 32 - row;
    bool needUpdate = false;

    if (rpm < rpmVals[row2]) {
      for (int col = 0; col < 8; col++) {
        ledsLeft[row2 * 8 + col] = CRGB::Black; // reset the necessary rows before re-lighting
         ledsRight[row * 8 + col] = CRGB::Black;
      }
      FastLED.show();
    } 
    if (rpm > rpmVals[row]) {
      for (int col = 0; col < 8; col++) {
        ledsLeft[row * 8 + col] = colors[row]; // light up the new row
         ledsRight[row * 8 + col] = colors[row];
      }
    } 
    FastLED.show();
  }
}
