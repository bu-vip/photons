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

void pingHandler(const char *event, const char *data) {
  Spark.publish("hereiam");
}

void sensorHandler(const char *event, const char *data) {
  uint16_t TCS_clear, TCS_red, TCS_green, TCS_blue;
  for (int j = 0; j <= 3; j++) {
    tcs.setInterrupt(false);      // turn on LED
    delay(60);  // takes 50ms to read
    tcs.getRawData(&TCS_red, &TCS_green, &TCS_blue, &TCS_clear);
    tcs.setInterrupt(true);  // turn off LED

    int lux_value = TCS_clear;


    sprintf(szInfo, "lux = %d", (int)lux_value);

    Spark.publish("colorinfo", szInfo);
    Particle.process(); // update the cloud
  }
}

void ledHandler(const char* event, const char* data) {
  std::string str_data = std::string(data);
  std::string led_on = "led_on";
  if (!str_data.compare(led_on)) { // check if the event's data is "led on"
    analogWrite(white, 255, freq); // turn LED on
    analogWrite(red, 255, freq);
    analogWrite(green, 255, freq);
    analogWrite(blue, 255, freq);
  } else {
    analogWrite(white, 0, freq); // turn LED off
    analogWrite(red, 0, freq);
    analogWrite(green, 0, freq);
    analogWrite(blue, 0, freq);
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
      Particle.subscribe("find_all_photons",pingHandler);
      Particle.subscribe("capture_sensors", sensorHandler);
      Particle.subscribe(getCoreID(), ledHandler);
  } else {
      Particle.publish("fatal","missing sensor");
      pinMode(red, OUTPUT);
      analogWrite(red, 255, freq); // makes it clear that something is wrong
  }
}
