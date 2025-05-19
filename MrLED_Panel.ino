/// @file    Blink.ino
/// @brief   Blink the first LED of an LED strip
/// @example Blink.ino

//Calc for translation of 8x8 panel ig
/*
 if (revert) {
      for (int panel = info.amount - 1; panel >= 0; panel--) {
        for (int col = info.dimension.width - 1; col >= 0; col--) {
          int offset = panel * info.dimension.size;  //offset to the next panel
          int row_start = row * info.dimension.width;
          panel_translator[row_start + col + offset] = num;
          num++;
        }
      }
      revert = false;
    } else {
      for (int panel = 0; panel < info.amount; panel++) {
        for (int col = 0; col < info.dimension.width; col++) {
          int offset = panel * info.dimension.size;  //offset to the next panel
          int row_start = row * info.dimension.width;
          panel_translator[row_start + col + offset] = num;
          num++;
        }
      }
      revert = true;
    }
*/

#include <FastLED.h>
#include <time.h>

#include "config.h"
#include "font.h"

#define TEST_HEIGHT 8
#define TEST_WIDTH 8

// array size is 192
const unsigned char test[] PROGMEM = {
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

// array size is 192
const unsigned char toad_fresse[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 255, 255,
  255, 255, 255, 255, 227, 21, 26, 227,
  21, 26, 227, 21, 26, 0, 0, 0,
  0, 0, 0, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 227, 21, 26, 227,
  21, 26, 227, 21, 26, 255, 255, 255,
  0, 0, 0, 227, 21, 26, 227, 21,
  26, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 227, 21, 26,
  0, 0, 0, 227, 21, 26, 227, 21,
  26, 255, 255, 255, 249, 207, 207, 249,
  207, 207, 249, 207, 207, 227, 21, 26,
  0, 0, 0, 255, 255, 255, 255, 255,
  255, 249, 207, 207, 0, 0, 0, 249,
  207, 207, 0, 0, 0, 255, 255, 255,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 249, 207, 207, 249, 207, 207, 249,
  207, 207, 249, 207, 207, 0, 0, 0,
  0, 0, 0, 249, 207, 207, 56, 163,
  235, 56, 163, 235, 255, 255, 255, 255,
  255, 255, 68, 73, 207, 249, 207, 207,
  0, 0, 0, 0, 0, 0, 147, 93,
  60, 147, 93, 60, 0, 0, 0, 147,
  93, 60, 147, 93, 60, 0, 0, 0
};

const unsigned char shy_guy[] PROGMEM = {
  0, 0, 0, 167, 18, 0, 167, 18,
  0, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 0, 0, 0,
  167, 18, 0, 167, 18, 0, 255, 255,
  255, 255, 255, 255, 0, 0, 0, 255,
  255, 255, 0, 0, 0, 255, 255, 255,
  0, 0, 0, 147, 93, 60, 255, 255,
  255, 255, 255, 255, 0, 0, 0, 255,
  255, 255, 0, 0, 0, 255, 255, 255,
  0, 0, 0, 167, 18, 0, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255,
  0, 0, 0, 167, 18, 0, 167, 18,
  0, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 0, 0, 0,
  167, 18, 0, 167, 18, 0, 147, 93,
  60, 167, 18, 0, 223, 251, 39, 223,
  251, 39, 147, 93, 60, 0, 0, 0,
  167, 18, 0, 147, 93, 60, 167, 18,
  0, 167, 18, 0, 167, 18, 0, 167,
  18, 0, 167, 18, 0, 147, 93, 60,
  0, 0, 0, 33, 52, 77, 33, 52,
  77, 33, 52, 77, 0, 0, 0, 33,
  52, 77, 33, 52, 77, 33, 52, 77
};

const unsigned char mised[] PROGMEM = {
  82, 89, 114, 82, 89, 114, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 82, 89, 114,
  82, 89, 114, 82, 89, 114, 16, 6,
  173, 16, 6, 173, 16, 6, 173, 16,
  6, 173, 16, 6, 173, 82, 89, 114,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  82, 89, 114, 255, 255, 255, 117, 255,
  255, 117, 255, 255, 255, 255, 255, 117,
  255, 255, 117, 255, 255, 255, 255, 255,
  82, 89, 114, 255, 255, 255, 117, 255,
  255, 0, 0, 0, 255, 255, 255, 0,
  0, 0, 117, 255, 255, 255, 255, 255,
  82, 89, 114, 255, 255, 255, 117, 255,
  255, 0, 0, 0, 255, 255, 255, 0,
  0, 0, 117, 255, 255, 255, 255, 255,
  82, 89, 114, 255, 255, 255, 246, 124,
  0, 255, 255, 255, 246, 124, 0, 255,
  255, 255, 246, 124, 0, 255, 255, 255,
  82, 89, 114, 82, 89, 114, 255, 255,
  255, 246, 124, 0, 246, 124, 0, 246,
  124, 0, 255, 255, 255, 82, 89, 114,
  82, 89, 114, 82, 89, 114, 82, 89,
  114, 244, 0, 0, 244, 0, 0, 244,
  0, 0, 82, 89, 114, 82, 89, 114,
  82, 89, 114, 244, 0, 0, 244, 0,
  0, 0, 0, 0, 244, 0, 0, 244,
  0, 0, 244, 0, 0, 244, 0, 0,
  82, 89, 114, 244, 0, 0, 244, 0,
  0, 244, 0, 0, 244, 0, 0, 244,
  0, 0, 244, 0, 0, 244, 0, 0,
  82, 89, 114, 244, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 244, 0, 0,
  164, 84, 0, 164, 84, 0, 244, 0,
  0, 244, 0, 0, 244, 0, 0, 244,
  0, 0, 244, 0, 0, 255, 255, 255,
  164, 84, 0, 82, 89, 114, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 82, 89, 114,
  164, 84, 0, 82, 89, 114, 255, 255,
  255, 255, 255, 255, 82, 89, 114, 255,
  255, 255, 255, 255, 255, 82, 89, 114,
  164, 84, 0, 246, 124, 0, 48, 126,
  255, 48, 126, 255, 82, 89, 114, 48,
  126, 255, 48, 126, 255, 246, 124, 0
};

// Define the array of leds
CRGB leds[NUM_LEDS];

struct PanelDimension {
  unsigned short size = P_SIZE;
  unsigned char width = P_WIDTH;
  unsigned char height = P_HEIGHT;
};

struct PanelInfo {
  int panel;
  short *translator;
  unsigned char amount = P_AMOUNT;
  unsigned char row;  //Height
  unsigned char col;  //Width
  struct PanelDimension dimension;
  CRGB::HTMLColorCode color = CRGB::Black;
};

//provides individuel sized panels
short *panel_translator = NULL;
void createTranslator(struct PanelInfo info) {
  bool revert = false;
  int num = 0;
  //TODO edit the panel_row to be also revert or normal because of panel constraints
  for (int panel_row = 0; panel_row < info.row; panel_row++) {
    for (int row = 0; row < info.dimension.height; row++) {
      if (revert) {
        for (int panel = 0; panel < info.col; panel++) {
          for (int col = info.dimension.width - 1; col >= 0; col--) {
            int offset = panel * info.dimension.size;  //offset to the next panel
            int row_offset = info.dimension.size * panel_row * info.col;
            int row_start = row * info.dimension.width + row_offset;
            info.translator[num] = row_start + col + offset;
            num++;
          }
        }
        revert = false;
      } else {
        for (int panel = 0; panel < info.col; panel++) {
          for (int col = 0; col < info.dimension.width; col++) {
            int offset = panel * info.dimension.size;  //offset to the next panel
            int row_offset = info.dimension.size * panel_row * info.col;
            int row_start = row * info.dimension.width + row_offset;
            info.translator[num] = row_start + col + offset;
            num++;
          }
        }
        revert = true;
      }
    }
  }
}

//Shows given char array of rgb values image.
//Color of PanelInfo will be ignored
void showImage(struct PanelInfo info, const unsigned char *image, unsigned char width, unsigned char height) {
  //TODO: Check if PanelInfo is same size like image -> else fallback or error?
  int max_image_size = width * height;
  const unsigned char *ptr = image;
  unsigned char r, g, b;
  for (int pixel = 0; pixel < max_image_size; pixel++) {
    r = *ptr;
    g = *(ptr + 1);
    b = *(ptr + 2);
    leds[info.translator[pixel] + info.panel * info.dimension.size].setRGB(r, g, b);
    ptr += 3;
  }

  FastLED.show();
}

/* Deprecated
const char single_panel_translator_overhead[P_SIZE]{
  28, 29, 30, 31,  //1
  27, 26, 25, 24,  //2
  20, 21, 22, 23,  //3
  19, 18, 17, 16,  //4
  12, 13, 14, 15,  //5
  11, 10, 9, 8,    //6
  4, 5, 6, 7,      //7
  3, 2, 1, 0       //8
};
*/

void showAscii(struct PanelInfo info, unsigned char ascii) {
  for (int pixel = 0; pixel < info.dimension.size; pixel++) {
    if (panel_ascii[ascii][pixel]) {
      if (info.color == CRGB::FairyLightNCC) {
        int r = rand() % 255, g = rand() % 255, b = rand() % 255;
        leds[info.translator[pixel] + info.panel * info.dimension.size].setRGB(r, g, b);
      } else {
        leds[info.translator[pixel] + info.panel * info.dimension.size] = info.color;
      }
    } else {
      leds[info.translator[pixel] + info.panel * info.dimension.size] = CRGB::Black;
    }
  }
  FastLED.show();
}

void shiftTranslator(short *translator, int size, int width, int height) {
  for (int row = 0; row < height; row++) {
    int row_start = row * width;
    short *temp = (short *)malloc(sizeof(short) * 1);
    if (temp != 0) {
      memmove(temp, translator + row_start, sizeof(short) * 1);
      memmove(translator + row_start, translator + row_start + 1, sizeof(short) * (width - 1));
      memmove(translator + row_start + width - 1, temp, sizeof(short) * 1);
      free(temp);
    }
  }

  for (int i = 0; i < size; i++) {
    Serial.printf("%d ", translator[i]);
  }
}

//slides the given chars to the left
//chars must be as big as panelInfo
void slideAsciiLeft(struct PanelInfo info, char *chars, int chars_size, int pixel) {
  //short *shift_translator = (short *)calloc(sizeof(short), info.amount * info.dimension.size);
  //memcpy(shift_translator, info.translator, info.amount * info.dimension.size);
  shiftTranslator(info.translator, info.amount * info.dimension.size, info.dimension.width, info.dimension.height);

  //TODO edit the panel_row to be also revert or normal because of panel constraints <- cpyd idk if it still applies

  //HERE CHANGE TO BE FOR WIDTH OF WHOLE PANEL COMBINED
  for (int panel_row = 0; panel_row < info.row; panel_row++) {
    for (int panel = 0; panel < info.col; panel++) {
      for (int row = 0; row < info.dimension.height; row++) {
        for (int col = 0; col < info.dimension.width; col++) {
          int offset = panel * info.dimension.size;  //offset to the next panel
          int row_offset = info.dimension.size * panel_row * info.col;
          int row_start = row * info.dimension.width + row_offset;
          if (panel_ascii['T'][row * info.dimension.width + col]) {
            leds[info.translator[row_start + col + offset]] = info.color;
          }else{
            leds[info.translator[row_start + col + offset]] = CRGB::Black;
          }
        }
      }
    }
  }
  FastLED.show();
}

void setup() {
  FastLED.addLeds<SK6812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.setCorrection(TypicalLEDStrip);

  panel_translator = (short *)calloc(sizeof(short), TEST_WIDTH * TEST_HEIGHT);
  struct PanelInfo info = { 0, panel_translator, 2, 1, 2, { 32, 4, 8 }, CRGB::FairyLightNCC };
  createTranslator(info);

  //hier iwie aus ner config lesen und alle Panels darin abspeichern
  //malloc in nen array und dies mit einer gesamtgröße gegrenzen, dass man Buffer_Overflows vom RP vermeidet

  Serial.begin(115200);
  srand(time(NULL));
}

short *translator = NULL;
struct PanelInfo info = {};

void loop() {
  Serial.print("hi\n");

  delay(1600);

  if (translator == NULL) {
    translator = (short *)calloc(sizeof(short), 32 * 4);

    info = { 0, translator, 4, 1, 4, { 32, 4, 8 }, CRGB::Green};

    createTranslator(info);
  }

  slideAsciiLeft(info, NULL, NULL, NULL);
}
