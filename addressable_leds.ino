#include "FastLED.h"
//#include <ESP8266WiFi.h>
//#include "Adafruit_MQTT.h"
//#include "Adafruit_MQTT_Client.h"
#include "Led.h"

// Potentiometer
#define USES_BRIGHTNESS_POT true
#define POT_BRIHTNESS_PIN A0

// Config
#define ANIMATION_FEED "tester-animation"
#define SPEED_FEED "tester-speed"

// Standard Config
#define BUTTON_PIN  0
#define BOARD_LED_PIN 3

// Wifi
#define WIFI_SSID "Bourke"
#define WIFI_PASS "b4d6e55e"

#define MQTT_SERV "io.adafruit.com"
#define MQTT_PORT 1883
#define MQTT_NAME "tjbourke"
#define MQTT_PASS "1a017b8f4d634e37b2c1e4c2afcbe976"

int potVal = 0;

int lastButtonState = 1;

//WiFiClient client;
//Adafruit_MQTT_Client mqtt(&client, MQTT_SERV, MQTT_PORT, MQTT_NAME, MQTT_PASS);
//Adafruit_MQTT_Subscribe animationFeed = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/feeds/" ANIMATION_FEED);
//Adafruit_MQTT_Subscribe speedFeed = Adafruit_MQTT_Subscribe(&mqtt, MQTT_NAME "/feeds/" SPEED_FEED);

Led led;

void setup()
{
  Serial.begin(9600);
  
  // Button
  pinMode(BUTTON_PIN, INPUT);
  pinMode(BOARD_LED_PIN, OUTPUT);
  
  // LEDs
  led.setup();

  // Wifi
  //Connect to WiFi
  //Serial.print("\n\nConnecting Wifi... ");
  //WiFi.begin(WIFI_SSID, WIFI_PASS);
  //while (WiFi.status() != WL_CONNECTED)
  //{
  //  delay(500);
  //}
  //Serial.println("Wifi is setup!");

  // Subscribe to the animation and speed topics
  //mqtt.subscribe(&animationFeed);
  //mqtt.subscribe(&speedFeed);

  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  buttonLoop();
  
  led.loop();
  
  // Potentiometer
  if(USES_BRIGHTNESS_POT) {
    potVal = analogRead(POT_BRIHTNESS_PIN);
    led.SetBrightness(potVal / 4); // Normalize to 0 to 255
  }
  
  //mqttLoop();
}

void buttonLoop()
{
  int buttonState = digitalRead(BUTTON_PIN);
  digitalWrite(BOARD_LED_PIN, HIGH);

  uint8_t animation = led.GetAnimation();
  if (buttonState != lastButtonState) {
    lastButtonState = buttonState;
    if (buttonState == 0) {
      animation++;
      led.SetAnimation(animation);
    }
  }
}

/*
void mqttLoop()
{
  // Wifi
  //Connect/Reconnect to MQTT
  MQTT_connect();
  
  uint16_t animateSpeed;
  uint8_t animation;

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

            led.SetAnimationSpeed(animateSpeed);
            
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
      led.SetAnimationName(a);
    }
    
    if (!mqtt.ping()) { mqtt.disconnect(); }
    delay(0);
  }
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
}*/
