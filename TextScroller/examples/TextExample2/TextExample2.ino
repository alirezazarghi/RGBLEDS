#include <FastLED.h>

#include <LEDMatrix.h>
#include <TextScroller.h>
#include <FontRobotron.h>

#define LED_PIN        2
#define COLOR_ORDER    GRB
#define CHIPSET        WS2812B

#define MATRIX_WIDTH   68
#define MATRIX_HEIGHT  7
#define MATRIX_ZIGZAG  true

#define NUM_LEDS  (MATRIX_WIDTH * MATRIX_HEIGHT)

CRGB leds[NUM_LEDS];
cLEDMatrix LEDMatrix(MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_ZIGZAG, leds);

cTextScroller ScrollingMsg;
#define MESSAGE_WIDTH   68
#define MESSAGE_HEIGHT  8
#define MESSAGE_Y       0

const unsigned char TxtDemo[] = { EFFECT_SCROLL_LEFT "         LEFT SCROLL"
                                  EFFECT_SCROLL_RIGHT "         LLORCS THGIR"
                                  EFFECT_SCROLL_DOWN "         SCR-DOWN          SCR-DOWN         " EFFECT_FRAME_RATE "\x04" " SCR-DOWN         " EFFECT_FRAME_RATE "\x00" " "
                                  EFFECT_SCROLL_UP "         SCROL-UP          SCROL-UP         " EFFECT_FRAME_RATE "\x04" " SCROL-UP         " EFFECT_FRAME_RATE "\x00" " "
                                  EFFECT_CHAR_UP EFFECT_SCROLL_LEFT "         UP"
                                  EFFECT_CHAR_RIGHT "  RIGHT"
                                  EFFECT_CHAR_DOWN "  DOWN"
                                  EFFECT_CHAR_LEFT "  LEFT"
                                  EFFECT_HSV_CV "\x00\xff\xff\x40\xff\xff" EFFECT_CHAR_UP "   HSV_CV 00-40"
                                  EFFECT_HSV_CH "\x00\xff\xff\x40\xff\xff" "   HSV_CH 00-40"
                                  EFFECT_HSV_AV "\x00\xff\xff\x40\xff\xff" "   HSV_AV 00-40"
                                  EFFECT_HSV_AH "\x00\xff\xff\xff\xff\xff" "   HSV_AH 00-FF"
                                  "         " EFFECT_HSV "\x00\xff\xff" "R" EFFECT_HSV "\x20\xff\xff" "A" EFFECT_HSV "\x40\xff\xff" "I" EFFECT_HSV "\x60\xff\xff" "N" EFFECT_HSV "\xe0\xff\xff" "B" EFFECT_HSV "\xc0\xff\xff" "O"
                                  EFFECT_HSV "\xa0\xff\xff" "W" EFFECT_HSV "\x80\xff\xff" "S" EFFECT_DELAY_FRAMES "\x00\x96" EFFECT_RGB "\xff\xff\xff" };

void setup()
{
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(255);
  FastLED.clear(true);
  delay(500);
  FastLED.showColor(CRGB::Red);
  delay(1000);
  FastLED.showColor(CRGB::Lime);
  delay(1000);
  FastLED.showColor(CRGB::Blue);
  delay(1000);
  FastLED.showColor(CRGB::White);
  delay(1000);
  FastLED.show();

  ScrollingMsg.SetFont(ROBOTRON_WIDTH, ROBOTRON_HEIGHT, ROBOTRON_CHAR_LOW, ROBOTRON_CHAR_HIGH, RobotronData);
  ScrollingMsg.Init(&LEDMatrix, MESSAGE_WIDTH, MESSAGE_HEIGHT, 0, MESSAGE_Y);
  ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
}


void loop()
{
  if (ScrollingMsg.UpdateText() == -1)
    ScrollingMsg.SetText((unsigned char *)TxtDemo, sizeof(TxtDemo) - 1);
  else
    FastLED.show();
  delay(10);
}

