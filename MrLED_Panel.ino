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

#define TEST_HEIGHT 8
#define TEST_WIDTH 8

// array size is 192
static const char test[] PROGMEM  = {
  161, 217, 235, 161, 217, 235, 161, 217, 
  235, 161, 217, 235, 161, 217, 235, 161, 
  217, 235, 161, 217, 235, 161, 217, 235, 
  161, 217, 235, 161, 217, 235, 244, 161, 
  177, 244, 161, 177, 244, 161, 177, 244, 
  161, 177, 161, 217, 235, 161, 217, 235, 
  161, 217, 235, 244, 161, 177, 244, 161, 
  177, 244, 161, 177, 244, 161, 177, 244, 
  161, 177, 244, 161, 177, 161, 217, 235, 
  161, 217, 235, 242, 123, 146, 244, 161, 
  177, 0, 0, 0, 244, 161, 177, 0, 
  0, 0, 244, 161, 177, 242, 123, 146, 
  242, 123, 146, 244, 161, 177, 244, 161, 
  177, 68, 73, 207, 244, 161, 177, 68, 
  73, 207, 244, 161, 177, 242, 123, 146, 
  242, 123, 146, 242, 123, 146, 241, 83, 
  147, 244, 161, 177, 244, 161, 177, 244, 
  161, 177, 241, 83, 147, 161, 217, 235, 
  161, 217, 235, 218, 82, 107, 242, 123, 
  146, 242, 123, 146, 244, 161, 177, 244, 
  161, 177, 218, 82, 107, 161, 217, 235, 
  161, 217, 235, 218, 82, 107, 218, 82, 
  107, 218, 82, 107, 161, 217, 235, 218, 
  82, 107, 218, 82, 107, 161, 217, 235
};

// Define the array of leds
CRGB leds[NUM_LEDS];

struct PanelInfo {
  int panel;
  CRGB::HTMLColorCode color = CRGB::Black;
  bool is_overhead;
};

void create_translation(short *panel_translator, int width, int height){

  bool revert = false;
  int ptr = 0;
  int cur_num = 0;
  for(int pos = 0; pos < height /*iwie abbruch wegen ptr out of bounce??*/; pos++){
    if(revert){
      int temp = cur_num;
      for(int cycle_rev = cur_num + width - 1; cycle_rev > temp; cycle_rev--){
        cur_num = cycle_rev; // das funktioniert safe nicht ! cur_num müsste das was cycle_rev am anfang war sein?
        panel_translator[ptr] = cur_num;
        ptr++;
      }
      revert = false;
    }else{
      for(int cycle_pos = cur_num; cycle_pos < cur_num + width; cycle_pos++){
        cur_num = cycle_pos;
        panel_translator[ptr] = cur_num;
        ptr++;
      }
      revert = true;
      return ;
    }
  }
}

const char single_panel_translator[PANEL_SIZE]{
  0, 1, 2, 3,      //1
  7, 6, 5, 4,      //2
  8, 9, 10, 11,    //3
  15, 14, 13, 12,  //4
  16, 17, 18, 19,  //5
  23, 22, 21, 20,  //6
  24, 25, 26, 27,  //7
  31, 30, 29, 28   //8
};

const char single_panel_translator_overhead[PANEL_SIZE]{
  28, 29, 30, 31,  //1
  27, 26, 25, 24,  //2
  20, 21, 22, 23,  //3
  19, 18, 17, 16,  //4
  12, 13, 14, 15,  //5
  11, 10, 9, 8,    //6
  4, 5, 6, 7,      //7
  3, 2, 1, 0       //8
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
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          } else {
            leds[single_panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;

        case 1:
          if (panel_two[i]) {
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          } else {
            leds[single_panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;

        case 2:
          if (panel_one[i]) {
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          } else {
            leds[single_panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
          }
          break;

        case 3:
          if (panel_two[i]) {
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          } else {
            leds[single_panel_translator[i] + panel * PANEL_SIZE] = CRGB::Black;
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
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;

        case 1:
          if (panel_two_s[i]) {
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;

        case 2:
          if (panel_three_s[i]) {
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
          }
          break;

        case 3:
          if (panel_four_s[i]) {
            leds[single_panel_translator[i] + panel * PANEL_SIZE].setRGB(r, g, b);
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

void led_ascii_shuffle() {
  for (int i = 0; i < 64; i++) {
    for (int pixel = 0; pixel < 32; pixel++) {
      if (panel_ascii[i][pixel]) {
        leds[single_panel_translator[pixel]] = CRGB::Red;
      } else {
        leds[single_panel_translator[pixel]] = CRGB::Black;
      }
    }
    FastLED.show();
    delay(500);
  }
}

void show_ascii(struct PanelInfo info, char ascii) {
  //use a random color
  if (info.color == CRGB::FairyLightNCC) {
    int r = rand() % 255;
    int g = rand() % 255;
    int b = rand() % 255;
    for (int pixel = 0; pixel < PANEL_SIZE; pixel++) {
      if (panel_ascii[ascii][pixel]) {
        if (info.is_overhead) {
          leds[single_panel_translator_overhead[pixel] + info.panel * PANEL_SIZE].setRGB(r, g, b);
        } else {
          leds[single_panel_translator[pixel] + info.panel * PANEL_SIZE].setRGB(r, g, b);
        }
      } else {
        if (info.is_overhead) {
          leds[single_panel_translator_overhead[pixel] + info.panel * PANEL_SIZE] = CRGB::Black;
        } else {
          leds[single_panel_translator[pixel] + info.panel * PANEL_SIZE] = CRGB::Black;
        }
      }
    }
  } else {
    //Use given color
    for (int pixel = 0; pixel < PANEL_SIZE; pixel++) {
      if (panel_ascii[ascii][pixel]) {
        if (info.is_overhead) {
          leds[single_panel_translator_overhead[pixel] + info.panel * PANEL_SIZE] = info.color;
        } else {
          leds[single_panel_translator[pixel] + info.panel * PANEL_SIZE] = info.color;
        }

      } else {
        if (info.is_overhead) {
          leds[single_panel_translator_overhead[pixel] + info.panel * PANEL_SIZE] = CRGB::Black;
        } else {
          leds[single_panel_translator[pixel] + info.panel * PANEL_SIZE] = CRGB::Black;
        }
      }
    }
  }

  FastLED.show();
}

short *panel_translator = NULL;

void setup() {
  FastLED.addLeds<SK6812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(25);
  FastLED.setCorrection(TypicalLEDStrip);

  panel_translator = (short *)calloc(sizeof(short), 8*8);

  create_translation(panel_translator, TEST_WIDTH, TEST_HEIGHT);

  //hier iwie aus ner config lesen und alle Panels darin abspeichern
  //malloc in nen array und dies mit einer gesamtgröße gegrenzen, dass man Buffer_Overflows vom RP vermeidet

  Serial.begin(115200);
  srand(time(NULL));
}

void loop() {
  Serial.print("hi\n");
  //rainbow_hi();
  //delay(2000);
  //sam();
  //wave();
  //delay(2000);
  //led_ascii_shuffle();
  //delay(2000);

  for (int panel = 0; panel < PANELS_AMOUNT; panel++) {
    struct PanelInfo panel_info = {};
    if (panel == 0 || panel == 1 || panel == 2) {
      panel_info = { panel, CRGB::FairyLightNCC, false };
    } else {
      panel_info = { panel, CRGB::FairyLightNCC, true };
    }

    show_ascii(panel_info, 'F');
  }

  delay(2000);

  for(int i = 0; i < TEST_WIDTH * TEST_HEIGHT; i++){
    Serial.printf("%d ", panel_translator[i]);
  }

}
