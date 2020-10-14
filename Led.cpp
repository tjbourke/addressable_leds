//#include "Arduino.h"
#include "FastLED.h"
#include "Led.h"

#define NUM_LEDS 70      // Length of LED strip
#define DEFAULT_ANIMATION 0
#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_ANIMATION_SPEED 100;

#define LED_PIN 4 // hardware SPI pin SCK
#define COLOR_ORDER GRB
#define LED_TYPE WS2811
#define MAX_INT_VALUE 65536

uint16_t animateSpeed = DEFAULT_ANIMATION_SPEED; // Number of frames to increment per loop
uint8_t  animation = DEFAULT_ANIMATION; // Active animation
uint8_t brightness = DEFAULT_BRIGHTNESS;  // Global brightness percentage

CRGB strip[NUM_LEDS];

uint16_t frame = 0;
  
Led::Led()
{

}

void Led::setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(strip, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(brightness);
  FastLED.clear();
}

void Led::loop()
{
  static uint8_t startIndex = 0;
  startIndex = startIndex + 1; 

  int baseColor = (animation - 10) * 10;

  CRGB color; 
      
  animation = animation % 35;
  switch(animation)
  {
  case 0:
    PaletteColors(strip, startIndex, RainbowColors_p, LINEARBLEND, frame);
    // Shinra Colors
    color = CRGB(245, 31, 2); // Red / Orange
    color = CHSV(2*.7083, 84*2.55, 71*2.55); // Red / Orange (too red)
    color = CHSV(53*.7083, 95*2.55, 70*2.55); // Yellow (Chest)
    //color = CHSV(191, 255, 150); // Purple
    //color = CHSV(255*.7083, 85*2.55, 45*2.55); // Purple
    //color = CHSV(125, 250, 148); // Teal / Mako
    //Solid(strip, color);
    break;
  case 1:
    RingPair(strip, frame); 
    break;
  case 2:
    DoubleChaser(strip,frame);
    break;
  case 3:
    WaveInt(strip,frame,180);
    //Segments(strip, frame, LINEARBLEND);
    break;
  case 4:  
    Wave(strip,frame,180);
    break;
  case 5:  //Blue spark (Slow)
    //Spark(strip,frame,255,188);   //Overloaded version of "Spark" with Hue value, 255 for fade is the slowest fade possible. 256 is on/off
    //delay(2);       //Slow things down a bit more for Slow Spark
    Fire(55,120,100); break;
    break;
  case 6: //Blue spark (fast)
    Spark(strip,frame,246,188);   //Overloaded version of "Spark" with Hue value, 246 fade is faster which makes for a sharper dropoff
    break;
  case 7:  //White spark (Slow)
    Spark(strip,frame,255);     //"Spark" function without hue make a white spark, 255 for fade is the slowest fade possible.
    delay(2);       //Slow things down a bit more for Slow Spark
    break;
  case 8: //White spark (fast)      //"Spark" function without hue make a white spark, 246 fade is faster which makes for a sharper dropoff
    Spark(strip,frame,245);
    break;
  case 9:
    RainbowSpark(strip,frame,240);    //240 for dropoff is a pretty sharp fade, good for this animation
    break;
  case 10: 
  case 11:
  case 12:
  case 13:
  case 14:
  case 15:
  case 16:
  case 17:
  case 18:
  case 19:
  case 20:
  case 21:
  case 22:
  case 23:
  case 24:
  case 25:
  case 26:
  case 27:
  case 28:
  case 29:
  case 30:
  case 31:
  case 32:
  case 33:
  case 34:
    PaletteColors(strip, startIndex, SetupPalette(baseColor, baseColor+10), LINEARBLEND, frame); break;
  default:
    delay(100);           //Animation OFF
  }
  
  FastLED.show();         //All animations are applied!..send the results to the strip(s)
  frame += animateSpeed;
}

uint8_t Led::GetAnimation()
{
  return animation;
}

void Led::SetAnimation(uint8_t anim)
{
  animation = anim;
}

void Led::Segments(CRGB strip[], uint8_t colorIndex, TBlendType blending)
{
    int segments [] = {37, 69, 102};
    
    CRGBPalette16 currentPalettes [3];
    currentPalettes[0] = CRGBPalette16(CHSV(95, 255, 255),  CHSV(95, 255, 255));
    currentPalettes[1] = CRGBPalette16(CHSV(160, 255, 255),  CHSV(160, 255, 255));
    currentPalettes[2] = CRGBPalette16(CHSV(70, 255, 255),  CHSV(70, 255, 255));
    
    int segment = 0;
    for( int i = 0; i < NUM_LEDS; i++) {
        for (int j = 0; j < sizeof(segments); j++) {
            if (segments[j] > i) {
                segment = j;
                break;
            }
        }
        
        strip[i] = ColorFromPalette(currentPalettes[segment], colorIndex, brightness, blending);
        colorIndex += 3;
    }
}

CRGBPalette16 Led::SetupPalette(int start, int end)
{
    CRGB dark = CHSV(start, 255, 255);
    CRGB light  = CHSV(end, 255, 255);
    
    return CRGBPalette16(dark,  light);
}


void Led::PaletteColors(CRGB strip[], uint8_t colorIndex, CRGBPalette16 palette, TBlendType blending, uint16_t animationFrame)
{
    for(int i = 0; i < NUM_LEDS; i++) {
        strip[i] = ColorFromPalette(palette, colorIndex, brightness, blending);
        colorIndex += 3;
    }
    
    FastLED.delay(1000 / animateSpeed);
}

void Led::TripleBounce(CRGB strip[], uint16_t frame)   //3 chaser animations offset by 120 degrees each
{
  FastLED.clear();    //Clear previous buffer
  Bounce(strip,frame,0);
  Bounce(strip,frame+(MAX_INT_VALUE/3),100);
  Bounce(strip,frame+(MAX_INT_VALUE/3)*2,150);
}

void Led::DoubleChaser(CRGB strip[], uint16_t frame)   //2 chaser animations offset 180 degrees
{
  FastLED.clear();    // Clear previous buffer
  frame = frame * 2;
  Ring(strip, frame, 0);
  Ring(strip, frame + (MAX_INT_VALUE / 2), 150);
}

void Led::RingPair(CRGB strip[], uint16_t frame)     //2 rings animations at inverse phases
{
  FastLED.clear();    // Clear previous buffer
  Ring(strip, frame, 30);
  Ring(strip, MAX_INT_VALUE - frame, 150);
}

void Led::RainbowSpark(CRGB targetStrip[], uint16_t animationFrame,uint8_t fade){    //Color spark where hue is function of frame
  Spark(targetStrip,animationFrame,fade,animationFrame/255);
  delay(20);
}



void Led::Solid(CRGB strip[], CRGB color) 
{
    fill_solid(strip, NUM_LEDS, color);
}

void Led::Fire(int Cooling, int Sparking, int SpeedDelay) {
  static byte heat[NUM_LEDS];
  int cooldown;
 
  // Step 1.  Cool down every cell a little
  for( int i = 0; i < NUM_LEDS; i++) {
    cooldown = random(0, ((Cooling * 10) / NUM_LEDS) + 2);
   
    if(cooldown>heat[i]) {
      heat[i]=0;
    } else {
      heat[i]=heat[i]-cooldown;
    }
  }
 
  // Step 2.  Heat from each cell drifts 'up' and diffuses a little
  for( int k= NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2]) / 3;
  }
   
  // Step 3.  Randomly ignite new 'sparks' near the bottom
  if( random(255) < Sparking ) {
    int y = random(7);
    heat[y] = heat[y] + random(160,255);
    //heat[y] = random(160,255);
  }

  // Step 4.  Convert heat to LED colors
  for( int j = 0; j < NUM_LEDS; j++) {
    setPixelHeatColor(j, heat[j] );
  }

  delay(SpeedDelay);
}

void Led::setPixelHeatColor (int Pixel, byte temperature) {
  // Scale 'heat' down from 0-255 to 0-191
  byte t192 = round((temperature/255.0)*191);
 
  // calculate ramp up from
  byte heatramp = t192 & 0x3F; // 0..63
  heatramp <<= 2; // scale up to 0..252
 
  // figure out which third of the spectrum we're in:
  if( t192 > 0x80) {                     // hottest
    setPixel(Pixel, 255, 255, heatramp);
  } else if( t192 > 0x40 ) {             // middle
    setPixel(Pixel, 255, heatramp, 0);
  } else {                               // coolest
    setPixel(Pixel, heatramp, 0, 0);
  }
}

void Led::setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   strip[Pixel].r = red;
   strip[Pixel].g = green;
   strip[Pixel].b = blue;
 #endif
}


//#######################################################################################################
//##                                PRIMATIVE ANIMATION FUNCTIONS                                      ##
//#######################################################################################################



//*********************     Bounce      ***************************
// Linear "Larson scanner" (or knight rider effect) with anti-aliasing
// Color is determined by "hue"
//*****************************************************************
void Led::Bounce(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue)
{
  uint16_t pos16;
  if (animationFrame < (MAX_INT_VALUE / 2))
  {
    pos16 = animationFrame * 2;
  
  }else{
    pos16 = MAX_INT_VALUE - ((animationFrame - (MAX_INT_VALUE/2))*2);
  }

  int position = map(pos16, 0, MAX_INT_VALUE, 0, ((NUM_LEDS) * 16));
  drawFractionalBar(targetStrip, position, 3, hue,0);
}




//************************          Ring           ******************************
// Anti-aliased cyclical chaser, 3 pixels wide
// Color is determined by "hue"
//*****************************************************
void Led::Ring(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue)
{
  uint8_t stripLength = sizeof(strip)/sizeof(CRGB);
  int pos16 = map(animationFrame, 0, MAX_INT_VALUE, 0, ((stripLength) * 16));
  drawFractionalBar(targetStrip, pos16, 3, hue,1);
}

//***************************   Wave [Float Math]  *******************************
// Squeezed sine wave  
// Uses slow, Arduino sin() function
// Squeezing achieved by using an exponential (^8) sin value
// Color is determined by "hue"
//***********************************************************************************
void Led::Wave(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue){
  FastLED.clear();    //Clear previous buffer
  float deg; 
  float value; 
  uint8_t stripLength = sizeof(strip)/sizeof(CRGB);
  for(uint8_t i=0;i<stripLength;i++)
  {
    deg=float(animationFrame+((MAX_INT_VALUE/stripLength)*i))/(float(MAX_INT_VALUE)) * 360.0;
    value = pow(sin(radians(deg)),8);    //Squeeeeeeze

    if(value>=0){   //Chop sine wave (no negative values)
      targetStrip[i] += CHSV(hue,255,value*256);
    }
  } 
}


//***************************   Wave [Integer Math]  *******************************
// unadulterated sine wave.  
// Uses FastLED sin16() and no float math for efficiency. 
// Since im stuck with integer values, exponential wave-forming is not possible (unless i'm wrong???)
// Color is determined by "hue"
//***********************************************************************************
void Led::WaveInt(CRGB targetStrip[], uint16_t animationFrame, uint8_t hue){
  FastLED.clear();
  uint8_t stripLength = sizeof(strip)/sizeof(CRGB);
  uint8_t value;
  for(uint8_t i=0;i<stripLength;i++)
  {
    value=(sin16(animationFrame+((MAX_INT_VALUE/stripLength)*i)) + (MAX_INT_VALUE/2))/256;   
    if(value>=0){   
      targetStrip[i] += CHSV(hue,255,value);
    }
  } 
}


//********************************   Color Spark  ***********************************
// Color of the sparks is determined by "hue"
// Frequency of sparks is determined by global var "animateSpeed"
// "animateSpeed" var contrained from 1 - 255 (0.4% - 100%)
// "fade" parameter specifies dropoff (next frame brightness = current frame brightness * (x/256)
// fade = 256 means no dropoff, pixels are on or off
// NOTE: this animation doesnt clear the previous buffer because the fade/dropoff is a function of the previous LED state
//***********************************************************************************
void Led::Spark(CRGB targetStrip[], uint16_t animationFrame,uint8_t fade, uint8_t hue){

  uint8_t stripLength = sizeof(strip)/sizeof(CRGB);
  uint16_t rand = random16();

    for(int i=0;i<stripLength;i++)
    {   
      targetStrip[i].nscale8(fade);
    }


  if(rand < (MAX_INT_VALUE / (256 - (constrain(animateSpeed,1,256)))))  ;
  {
    targetStrip[rand % stripLength].setHSV(hue,255,255);
  }
}


//******************************       Spark       **********************************
// Same as color spark but no hue value, // in HSV white is any hue with 0 saturation
// Frequency of sparks is a percentage mapped to global var "animateSpeed"
// "animateSpeed" var contrained from 1 - 255 (0.4% - 100%)
// "fade" parameter specifies dropoff (next frame brightness = current frame brightness * (x/256)
// fade = 256 means no dropoff, pixels are on or off
// NOTE: this animation doesnt clear the previous buffer because the fade/dropoff is a function of the previous LED state
//***********************************************************************************
void Led::Spark(CRGB targetStrip[], uint16_t animationFrame,uint8_t fade){
  uint8_t stripLength = sizeof(strip)/sizeof(CRGB);
  uint16_t rand = random16();
  
  for(int i=0;i<stripLength;i++)
    {   
      targetStrip[i].nscale8(fade);
    }
  

  if(rand < (MAX_INT_VALUE / (256 - (constrain(animateSpeed,1,255)))))
  {
    targetStrip[rand % stripLength].setHSV(0,0,255);
  }

}



//Anti-aliasing code care of Mark Kriegsman Google+: https://plus.google.com/112916219338292742137/posts/2VYNQgD38Pw
void Led::drawFractionalBar(CRGB targetStrip[], int pos16, int width, uint8_t hue, bool wrap)
{
  uint8_t stripLength = sizeof(strip)/sizeof(CRGB);
  uint8_t i = pos16 / 16; // convert from pos to raw pixel number

  uint8_t frac = pos16 & 0x0F; // extract the 'factional' part of the position
  uint8_t firstpixelbrightness = 255 - (frac * 16);
  
  uint8_t lastpixelbrightness = 255 - firstpixelbrightness;

  uint8_t bright;
  for (int n = 0; n <= width; n++) {
    if (n == 0) {
      // first pixel in the bar
      bright = firstpixelbrightness;
    }
    else if (n == width) {
      // last pixel in the bar
      bright = lastpixelbrightness;
    }
    else {
      // middle pixels
      bright = 255;
    }

    targetStrip[i] += CHSV(hue, 255, bright );
    i++;
    if (i == stripLength)
    {
      if (wrap == 1) {
        i = 0; // wrap around
      }
      else{
        return;
      }
    }
  }
}
