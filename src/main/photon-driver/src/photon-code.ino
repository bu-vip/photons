#include "Adafruit_TCS34725.h"
#include <string>
boolean commonAnode = false;
char szInfo[128];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

int white = A5;
int red = A4;
int green = WKP;
int blue = TX;
int freq = 1000;

// getCoreID was copied from the community forum user dermotos
// https://community.particle.io/t/device-id-stored-in-core/2647/8
String getCoreID()
{
  String coreIdentifier = "";
  int maxIDlength = 12;

  char id[maxIDlength];
  memcpy(id, (char *)ID1, maxIDlength);
  char hex_digit;
  for (int i = 0; i < maxIDlength; ++i)
  {
    hex_digit = 48 + (id[i] >> 4);
    if (57 < hex_digit)
     hex_digit += 39;
     coreIdentifier = coreIdentifier + hex_digit;
    hex_digit = 48 + (id[i] & 0xf);
   if (57 < hex_digit)
     hex_digit += 39;
   coreIdentifier = coreIdentifier + hex_digit;
 }
 return coreIdentifier;
}

void captureSensor() {
  uint16_t TCS_clear, TCS_red, TCS_green, TCS_blue;
  for (int j = 0; j <= 3; j++) {
    tcs.setInterrupt(false);      // turn on LED
    delay(300);  // takes 50ms to read
    tcs.getRawData(&TCS_red, &TCS_green, &TCS_blue, &TCS_clear);
    tcs.setInterrupt(true);  // turn off LED

    int lux_value = TCS_clear;


    sprintf(szInfo, "lux = %d", (int)lux_value);

    Spark.publish("colorinfo", szInfo);
    Particle.process(); // update the cloud
  }
}

void ledOn() {
    analogWrite(white, 255, freq); // turn LED on
    analogWrite(red, 255, freq);
    analogWrite(green, 255, freq);
    analogWrite(blue, 255, freq);
}

void ledOff() {
  analogWrite(white, 0, freq); // turn LED off
  analogWrite(red, 0, freq);
  analogWrite(green, 0, freq);
  analogWrite(blue, 0, freq);
}

void cloudHandler(const char* event, const char* data) {
  const std::string str_data = std::string(data);
  const std::string led_on = "led_on";
  const std::string led_off = "led_off";
  const std::string capture_sensors = "capture_sensor";
  const std::string ping = "ping";
  if (!str_data.compare(led_on)) {
    ledOn();
  } else if (!str_data.compare(led_off)) {
    ledOff();
  } else if (!str_data.compare(capture_sensors)) {
    captureSensor();
  } else if (!str_data.compare(ping)) {
    Particle.publish("hereiam", getCoreID());
  } else {
    Particle.publish("error", "published command could not be interpreted");
  }
}

void setup() {
  Particle.publish("flashed");
  if (tcs.begin()) {
      pinMode(white, OUTPUT);
      pinMode(red, OUTPUT);
      pinMode(green, OUTPUT);
      pinMode(blue, OUTPUT);
      Serial.begin(9600);
      Particle.subscribe(getCoreID(), cloudHandler);
      Particle.subscribe("all_photons", cloudHandler);
  } else {
      Particle.publish("fatal","missing sensor");
      pinMode(red, OUTPUT);
      analogWrite(red, 255, freq); // makes it clear that something is wrong
  }
}
