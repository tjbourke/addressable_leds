#ifndef Led_h
#define Led_h

//#include "Arduino.h"

class Led
{
  public:
    Led();
    void setup();
    void loop();

    void Segments(CRGB strip[], uint8_t colorIndex, TBlendType blending);
    CRGBPalette16 SetupPalette(int start, int end);
    void PaletteColors(CRGB strip[], uint8_t colorIndex, CRGBPalette16 palette, TBlendType blending, uint16_t animationFrame);
    void TripleBounce(CRGB strip[], uint16_t frame);
    void DoubleChaser(CRGB strip[], uint16_t frame);
    void RingPair(CRGB strip[], uint16_t frame);
    void RainbowSpark(CRGB targetStrip[], uint16_t animationFrame,uint8_t fade);
    void Solid(CRGB strip[], CRGB color);
    void Fire(int Cooling, int Sparking, int SpeedDelay);
    void setPixelHeatColor (int Pixel, byte temperature);
    void setPixel(int Pixel, byte red, byte green, byte blue);

    void Bounce(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue);
    void Ring(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue);
    void Wave(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue);
    void WaveInt(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue);
    void Spark(CRGB targetStrip[], uint16_t animationFrame,uint8_t fade, uint8_t hue);
    void Spark(CRGB targetStrip[], uint16_t animationFrame,uint8_t fade);
    void drawFractionalBar(CRGB targetStrip[], int pos16, int width, uint8_t hue, bool wrap);
};

#endif
