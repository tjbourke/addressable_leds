#include "FastLED.h"
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "Led.h"

// Config
#define NUM_LEDS 70      // Length of LED strip
#define DEFAULT_ANIMATION 0
#define DEFAULT_BRIGHTNESS 255
#define DEFAULT_ANIMATION_SPEED 100;

#define ANIMATION_FEED "tester-animation"
#define SPEED_FEED "tester-speed"

// Standard Config
#define BUTTON_PIN  0
#define BOARD_LED_PIN 3
#define LED_PIN 4 // hardware SPI pin SCK
#define COLOR_ORDER GRB
#define LED_TYPE WS2811
#define MAX_INT_VALUE 65536

// Wifi
#define WIFI_SSID "Bourke"
#define WIFI_PASS "b4d6e55e"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "tjbourke"
#define MQTT_PASS "1a017b8f4d634e37b2c1e4c2afcbe976"

//uint16_t animateSpeed = DEFAULT_ANIMATION_SPEED; // Number of frames to increment per loop
//uint8_t  animation = DEFAULT_ANIMATION; // Active animation
//uint8_t brightness = DEFAULT_BRIGHTNESS;  // Global brightness percentage

//CRGB strip[NUM_LEDS];
//uint16_t frame = 0;
int lastButtonState = 1;

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
Adafruit_MQTT_Subscribe animationFeed = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/feeds/" ANIMATION_FEED);
Adafruit_MQTT_Subscribe speedFeed = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/feeds/" SPEED_FEED);


struct animationMap {
  String name;
  uint8_t number;
};

animationMap aMap[] = {
  (animationMap){"rainbow", 0},
  (animationMap){"ring", 1},  
  (animationMap){"chaser", 2},
  (animationMap){"segments", 3},
  (animationMap){"wave", 4},
  (animationMap){"fire", 5},
  (animationMap){"thunderstorm", 8},
  (animationMap){"rainbow thunderstorm", 9},
  (animationMap){"red", 10},
  (animationMap){"dark orange", 11},
  (animationMap){"orange", 12},
  (animationMap){"gold", 13},
  (animationMap){"yellow", 14},
  (animationMap){"yellow green", 17},
  (animationMap){"light green", 18},
  (animationMap){"green", 19},
  (animationMap){"teal", 20},
  (animationMap){"light blue", 21},
  (animationMap){"aqua", 22},
  (animationMap){"sky blue", 23},
  (animationMap){"blue", 24},
  (animationMap){"royal blue", 25},
  (animationMap){"light purple", 29},
  (animationMap){"purple", 30},
  (animationMap){"light pink", 31},
  (animationMap){"pink", 32},
  (animationMap){"dark pink", 33},
  (animationMap){"fuchsia", 34}
};

Led led;

void setup()
{
  Serial.begin(9600);
  
  // Button
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BOARD_LED_PIN, OUTPUT);
  
  // LEDs
  led.setup();
//  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(strip, NUM_LEDS).setCorrection(TypicalLEDStrip);
//  FastLED.setBrightness(brightness);
//  FastLED.clear();

  // Wifi
  //Connect to WiFi
  Serial.print("\n\nConnecting Wifi... ");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }

  Serial.println("OK!");

  // Subscribe to the animation and speed topics
  mqtt.subscribe(&animationFeed);
  mqtt.subscribe(&speedFeed);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  buttonLoop();
  //ledLoop();
  led.loop();
  mqttLoop();
}

void buttonLoop()
{
  /*
  int buttonState = digitalRead(BUTTON_PIN);
  digitalWrite(BOARD_LED_PIN, HIGH);

  if (buttonState != lastButtonState) {
    if (buttonState == 0) {
      animation++;
    }
  }
  */
}

void mqttLoop()
{
  /*
  // Wifi
  //Connect/Reconnect to MQTT
  MQTT_connect();

  //Read from our subscription queue until we run out, or
  //wait up to 5 seconds for subscription to update
  Adafruit_MQTT_Subscribe * subscription;
  while(subscription = mqtt.readSubscription(1)) {
    //If we're in here, a subscription updated...
    if (subscription == &speedFeed) {
        char *animSpeedString = (char *)speedFeed.lastread;
        int animSpeed = atoi(animSpeedString);
        if (animSpeed > 0 && animSpeed <= 1000) {
            animateSpeed = animSpeed;
            Serial.print("Speed changed to: ");
            Serial.println(animSpeed);
            Serial.println(animateSpeed);
        }
    }
    if (subscription == &animationFeed)
    {
      char *animationName = (char *)animationFeed.lastread;
      String a = (String)animationName;
      a.toLowerCase();

      if (a == "next") {
        animation++;
      } else {
        for (int i = 0; i < sizeof(aMap); i++) {
          if (aMap[i].name == a) {
            animation = aMap[i].number;
          }
        }
      }
      
      Serial.print("Animation: ");
      Serial.println(animation);
    }
    
    if (!mqtt.ping()) { mqtt.disconnect(); }
    delay(0);
  }
  */
}


void MQTT_connect() 
{
  int8_t ret;
  // Stop if already connected
  if (mqtt.connected())
  {
    return;
  }

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) // connect will return 0 for connected
  { 
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 1 second...");
    mqtt.disconnect();
    delay(1000);  // wait 1 second
    retries--;
    if (retries == 0) 
    {
      // basically die and wait for WDT to reset me
      while (1);
    }
  }
  Serial.println("MQTT Connected!");
}
