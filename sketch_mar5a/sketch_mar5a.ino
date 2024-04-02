// #define sensor A0

// // int wave = 0;
// int rev = 0;
// int rpm = 0;
// int curr = 0;

// unsigned long time;

// void setup() {
//   Serial.begin(9600);

// }

// void loop() {
//   static int last = HIGH;
//   static int curr = 0;
//   // rev = 0;
//   // unsigned long StartTime = millis();
//   // unsigned long currTime = millis();
//   // while (currTime - StartTime < 1) {
//     // wave = analogRead(sensor);
//     // if (wave < 900 && wave > 100) {
//     //   rev++;
//     // }
//   //   if (wave < 50) {
//   //     rev++;
//   //   }
//   //   currTime = millis();
//   // }
//   curr = analogRead(sensor);;
//   if (last == HIGH && curr == LOW) {
//     rev++;
//   }
//   last = curr;
//   // if (wave < 50) {
//   //     rev++;
//   //   }
  
//   Serial.println(rev);
//   delay(1);
// }

// v1
// int sensor = A0;
// #define sensor A0
// int wave;
// int rev;
// unsigned long time = millis();

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600);
//   // pinMode(sensor, INPUT);
// }

// void loop() {
//   // put your main code here, to run repeatedly:
//   wave = analogRead(sensor);
  
//   // unsigned long currtime = millis();
//   // while (currtime < 1000) {
//   //   rev += wave;
//   // }
//   // if ()
//   // if (wave == 0.5) {
//   //   rev++;
//   // }
//   // rev += wave;

//   Serial.println(wave);
//   delay(1);
// }


// v2
// float rev = 0;
// int rpm_value;
// int prev = 0;
// float t;

// void interrupt() {
//   rev++;
// }

// void setup() {
//   Serial.begin(9600);
//   attachInterrupt(2, interrupt, RISING);
// }

// void loop() {
//   delay(1000);
//   detachInterrupt(2);
//   t = millis() - prev;
//   rpm_value = (rev/t) * 60000;
//   prev = millis();
//   rev = 0;
//   Serial.println(rpm_value);
//   attachInterrupt(2, interrupt, RISING);
// }


// v3
// const int sensorPin = 2; // Sensor connected to pin 2
// volatile int rotations;   // Count rotations
// unsigned long lastMillis; // Last time update

// void setup() {
//   Serial.begin(9600);
//   pinMode(sensorPin, INPUT);
//   attachInterrupt(digitalPinToInterrupt(sensorPin), countRotation, RISING); // Use RISING for Hall effect sensor, CHANGE for IR
//   rotations = 0;
//   lastMillis = millis();
// }

// void loop() {
//   unsigned long currentMillis = millis();
//   if (currentMillis - lastMillis >= 1000) { // Update every second
//     noInterrupts(); // Disable interrupts to read rotations safely
//     Serial.print("RPM: ");
//     Serial.println(rotations * 60); // Convert rotations per second to RPM
//     rotations = 0; // Reset rotation count
//     lastMillis = currentMillis;
//     interrupts(); // Re-enable interrupts
//   }
// }

// void countRotation() {
//   rotations++;
// }



// v4
// #include <Wire.h>
// float value=0;
// float rev=0;
// int  rpm;
// int oldtime=0;        
// int time;

// void isr()          //interrupt  service routine
// {
// rev++;
// }

// void setup()
// {
// Serial.begin(9600);
// // digitalWrite(2 ,HIGH);// Instead  of using a pull up resistor
// attachInterrupt(2,isr,RISING);  //attaching the interrupt
// }

// void  loop()
// {
// delay(2000);// 2 second delay
// detachInterrupt(2);           //detaches  the interrupt while calculating
// time=millis()-oldtime;        //finds the time  
// rpm=(rev/time)*60000;         //calculates rpm
// oldtime=millis();             //saves  the current time
// rev=0;
// Serial.println("RPM:");
// Serial.println(rpm); 
// attachInterrupt(2,isr,RISING);
// }


// v5
// #include <Wire.h>

// volatile float rev = 0; // Use volatile for variables changed in ISR
// float rpm;
// unsigned long oldTime = 0;        
// unsigned long currentTime; // Use unsigned long for time tracking

// void isr() { // Interrupt service routine
//   rev++;
// }

// void setup() {
//   Serial.begin(9600);
//   attachInterrupt(digitalPinToInterrupt(2), isr, RISING); // Correct way to attach an interrupt
//   oldTime = millis(); // Initialize oldTime
// }

// void loop() {
//   delay(1000); // 1 second delay
//   detachInterrupt(digitalPinToInterrupt(2)); // Detaches the interrupt while calculating

//   currentTime = millis() - oldTime; // Finds the elapsed time in milliseconds
//   if(currentTime > 0) { // Prevent division by zero
//     rpm = (rev / (currentTime / 1000.0)) * 60; // Calculates RPM, converting ms to seconds
//   } else {
//     rpm = 0;
//   }
  
//   oldTime = millis(); // Updates oldTime for the next calculation
//   rev = 0; // Reset revolutions count
//   Serial.print("RPM: ");
//   Serial.println(rpm, 2); // Print with 2 decimal places for accuracy
//   attachInterrupt(digitalPinToInterrupt(2), isr, RISING); // Re-attaches the interrupt
// }





int rev = 0;
const short int pinA = 4;

// for led
#include <FastLED.h>
#define NUM_LEDS 256
#define DATA_PIN_1 12
#define DATA_PIN_2 12
#include <Wire.h>     
// #include "rgb_lcd.h" 

// rgb_lcd lcd; 
float value=0;
// float rev=0;
int rpm;
int rpmMax = 500;
// int oldtime=0;
// int time;
int rpmVals[32];
CRGB colors[] =  {0XFF0000, 0XFFA500, 0XFFFF00, 0X008000, 0X0000ff, 0X4B0082, 0XEE82EE, 0XFFFFFF};
CRGB ledsLeft[NUM_LEDS];
// CRGB ledsRight[NUM_LEDS];





void setup() {
  pinMode(pinA, INPUT);
  // digitalWirte()
  Serial.begin(9600);

  // for led
  FastLED.addLeds<WS2812,DATA_PIN_1,RGB>(ledsLeft,NUM_LEDS);
  // FastLED.addLeds<WS2812,DATA_PIN_2,RGB>(ledsRight,NUM_LEDS);
  FastLED.setBrightness(10);
  for (int i = 0; i < 32; i++) {
    rpmVals[i] = i * (rpmMax / 31);
    // fill_gradient_RGB( colors,
              //     0, 0xF0F8FF,
            //    31,   0xFF6437  );
            // also, empty the colors array
  }



}

void loop() {
  unsigned long startTime = millis();
  unsigned long currTime = millis();
  rev = 0;
  static int last = 1;
  static int members = 5;

  // int curr = digitalRead(pinA);

  while (currTime - startTime <= 1000) {
    int curr = digitalRead(pinA);
    if ((last == 1) && (curr == 0)) {
      rev++;
    }
    last = curr;
    // Serial.println(currTime - startTime);
    Serial.println(rev);

    currTime = millis();
  }


  // if ((last == 1) && (curr == 0)) {
  //   rev++;
  // }
  // last = curr;

  rpm = rev * 60 / members;
  Serial.println(rpm);
  // delay(1);

  // rpm = rev * 30;

  // for (int row = 31; row >= 0; row--) {
  //   if (rpm < rpmVals[row]) {
  //     for (int col = 0; col < 8; ++col) {
  //       ledsLeft[row * 8 + col] = CRGB::Black; // reset the necessary rows before re-lighting
  //       // ledsRight[row * 8 + col] = CRGB::Black;
  //     }
  //     FastLED.show();
  //   } 
  // }
  // for (int row = 0; row < 32; row++) {
  //   if (rpm > rpmVals[row]) {
  //     for (int col = 0; col < 8; ++col) {
  //       ledsLeft[row * 8 + col] = colors[(row + 1) / 4]; // light up the new row
  //       // ledsRight[row * 8 + col] = colors[(row + 1) / 4];
  //     }
  //   } 
  //   FastLED.show();
  // }

  //  rpm = 1200;
  for (int row = 0; row < 32; row++) {
    int row2 = 32 - row;
    bool needUpdate = false;

    if (rpm < rpmVals[row2]) {
      for (int col = 0; col < 8; col++) {
        ledsLeft[row2 * 8 + col] = CRGB::Black; // reset the necessary rows before re-lighting
        // ledsRight[row * 8 + col] = CRGB::Black;
      }
      FastLED.show();
      // needUpdate = true;
    } 
    if (rpm > rpmVals[row]) {
      for (int col = 0; col < 8; col++) {
        ledsLeft[row * 8 + col] = colors[(row) / 4]; // light up the new row
        // ledsRight[row * 8 + col] = colors[(row + 1) / 4];
      }
      // FastLED.show();
      // needUpdate = true;
    } 
    FastLED.show();
    // if (needUpdate) {
    //   FastLED.show();
    // }
  }

  // delay(2000);
}
