int rev = 0;
const short int pinA = 4;

// for led
#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN_1 12
#include <Wire.h>     

float value = 0;
int rpm;
int rpmMax = 500;
int rpmVals[32];
CRGB colors[] =  {0XFF0000, 0XFFA500, 0XFFFF00, 0X008000, 0X0000ff, 0X4B0082, 0XEE82EE, 0XFFFFFF};
CRGB ledsLeft[NUM_LEDS];

void setup() {
  pinMode(pinA, INPUT);
  Serial.begin(9600);

  // for led
  FastLED.addLeds<WS2812,DATA_PIN_1,RGB>(ledsLeft,NUM_LEDS);
  FastLED.setBrightness(10);
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
      }
      FastLED.show();
    } 
    if (rpm > rpmVals[row]) {
      for (int col = 0; col < 8; col++) {
        ledsLeft[row * 8 + col] = colors[(row) / 4]; // light up the new row
      }
    } 
    FastLED.show();
  }
}
