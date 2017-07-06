#include "Adafruit_TCS34725.h"
#include <string>
boolean commonAnode = false;
char szInfo[128];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);
boolean missing_sensor = false;

int white = A5;
int red = A4;
int freq = 1000;

String getCoreID()
{
  String coreIdentifier = "";
  char id[12];
  memcpy(id, (char *)ID1, 12);
  char hex_digit;
  for (int i = 0; i < 12; ++i)
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
    Particle.process();
  }
}

void ledHandler(const char* event, const char* data) {
  std::string str_data = std::string(data);
  std::string led_on = "led_on";
  if (!str_data.compare(led_on)) {
    analogWrite(white, 255, freq);
  } else {
    analogWrite(white, 0, freq);
  }
}

void setup() {
  Particle.publish("flashed");
  if (tcs.begin()) {
      missing_sensor = false;
      pinMode(white, OUTPUT);
      pinMode(red, OUTPUT);
      Serial.begin(9600);
      Particle.subscribe("capture_sensors", sensorHandler);
      Particle.subscribe(getCoreID(), ledHandler);
  } else {
      missing_sensor = true;
      Particle.publish("fatal","missing sensor");
  }
}
