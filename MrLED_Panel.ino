/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

//blank_panel
/*
bool panel_one_s[PANEL_SIZE] = {
  0, 0, 0, 0,  //1
  0, 0, 0, 0,  //2
  0, 0, 0, 0,  //3
  0, 0, 0, 0,  //4
  0, 0, 0, 0,  //5
  0, 0, 0, 0,  //6
  0, 0, 0, 0,  //7
  0, 0, 0, 0,  //8
};
*/

#include <FastLED.h>
#include <time.h>

#include "config.h"
#include "font.h"

// Define the array of leds
CRGB leds[NUM_LEDS];

const char panel_translator[PANEL_SIZE]{
  0, 1, 2, 3,      //1
  7, 6, 5, 4,      //2
  8, 9, 10, 11,    //3
  15, 14, 13, 12,  //4
  16, 17, 18, 19,  //5
  23, 22, 21, 20,  //6
  24, 25, 26, 27,  //7
  31, 30, 29, 28   //8
};

bool panel_one[PANEL_SIZE] = {
  1, 0, 0, 1,  //1
  1, 0, 0, 1,  //2
  1, 0, 0, 1,  //3
  1, 1, 1, 1,  //4
  1, 1, 1, 1,  //5
  1, 0, 0, 1,  //6
  1, 0, 0, 1,  //7
  1, 0, 0, 1,  //8
};

bool panel_two[PANEL_SIZE] = {
  0, 1, 1, 0,  //1
  0, 1, 1, 0,  //2
  0, 0, 0, 0,  //3
  0, 0, 0, 0,  //4
  0, 1, 1, 0,  //5
  0, 1, 1, 0,  //6
  0, 1, 1, 0,  //7
  0, 1, 1, 0,  //8
};


//----------------------


bool panel_one_s[PANEL_SIZE] = {
  0, 1, 1, 1,  //1
  1, 0, 0, 0,  //2
  1, 0, 0, 0,  //3
  0, 1, 1, 0,  //4
  0, 0, 0, 1,  //5
  0, 0, 0, 1,  //6
  0, 0, 0, 1,  //7
  1, 1, 1, 0,  //8
};

bool panel_two_s[PANEL_SIZE] = {
  0, 1, 1, 0,  //1
  1, 0, 0, 1,  //2
  1, 0, 0, 1,  //3
  1, 0, 0, 1,  //4
  1, 1, 1, 1,  //5
  1, 0, 0, 1,  //6
  1, 0, 0, 1,  //7
  1, 0, 0, 1,  //8
};

bool panel_three_s[PANEL_SIZE] = {
  1, 1, 1, 1,  //1
  1, 0, 1, 0,  //2
  1, 0, 1, 0,  //3
  1, 0, 1, 0,  //4
  1, 0, 1, 0,  //5
  1, 0, 1, 0,  //6
  1, 0, 1, 0,  //7
  1, 0, 1, 0,  //8
};

bool panel_four_s[PANEL_SIZE] = {
  1, 0, 1, 1,  //1
  1, 0, 1, 1,  //2
  1, 0, 1, 1,  //3
  1, 0, 1, 1,  //4
  1, 0, 0, 0,  //5
  1, 0, 0, 0,  //6
  1, 0, 1, 1,  //7
  1, 0, 1, 1,  //8
};


void rainbow_hi() {
  for (int panel = 0; panel < PANELS_AMOUNT; panel++) {
    for (int i = 0; i < PANEL_SIZE; i++) {
      int r = rand() % 255;
      int g = rand() % 255;
      int b = rand() % 255;

      switch (panel) {
        case 0:
          if (panel_one[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }else{
            leds[panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;

        case 1:
          if (panel_two[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }else{
            leds[panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;

        case 2:
          if (panel_one[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }else{
            leds[panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;

        case 3:
          if (panel_two[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }else{
            leds[panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;
      }
    }
  }
  FastLED.show();
  delay(80);
}

void sam() {
  for (int panel = 0; panel < PANELS_AMOUNT; panel++) {
    for (int i = 0; i < PANEL_SIZE; i++) {
      int r = rand() % 255;
      int g = rand() % 255;
      int b = rand() % 255;

      switch (panel) {
        case 0:
          if (panel_one_s[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;

        case 1:
          if (panel_two_s[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;

        case 2:
          if (panel_three_s[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;

        case 3:
          if (panel_four_s[i]) {
            leds[panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;
      }
    }
  }
  FastLED.show();
  delay(80);
}

void wave() {

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Aquamarine;
    FastLED.show();
    delay(1);
  }

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
    delay(1);
  }
}

void led_ascii_shuffle(){
  for (int i = 0; i < 64; i++) {
    for (int pixel = 0; pixel < 32; pixel++) {
      if (panel_ascii[i][pixel]) {
        leds[panel_translator[pixel]] = CRGB::Red;
      }else{
        leds[panel_translator[pixel]] = CRGB::Black;
      }
    }
    FastLED.show();
    delay(500);

  }
}

void show_ascii(int panel, char ascii, CRGB::HTMLColorCode color){
  if(color == CRGB::FairyLightNCC){
          int r = rand() % 255;
      int g = rand() % 255;
      int b = rand() % 255;
    for(int pixel = 0; pixel < PANEL_SIZE; pixel++){
        if(panel_ascii[ascii][pixel]){
          leds[panel_translator[pixel] + panel * PANEL_SIZE].setRGB(r, g, b);
        }else{
            leds[panel_translator[pixel] + panel * PANEL_SIZE] = CRGB::Black;
          }
    }
  }else{

    for(int pixel = 0; pixel < PANEL_SIZE; pixel++){
        if(panel_ascii[ascii][pixel]){
          leds[panel_translator[pixel] + panel * PANEL_SIZE] = color;
        }else{
            leds[panel_translator[pixel] + panel * PANEL_SIZE] = CRGB::Black;
          }
    }
    }
    
      FastLED.show();
}

void setup() {
  FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(25);
  FastLED.setCorrection(TypicalLEDStrip);

  Serial.begin(115200);
  srand(time(NULL));
}

void loop() {
  Serial.print("hi\n");  
  rainbow_hi();
  delay(2000);
  //sam();
  wave();
  delay(2000);
  //led_ascii_shuffle();
  delay(2000);

  for(int panel = 0; panel < PANELS_AMOUNT; panel++){
          show_ascii(panel, 'F', CRGB::FairyLightNCC);
  }
  show_ascii(2, '2', CRGB::BlueViolet);
      delay(2000);
}
