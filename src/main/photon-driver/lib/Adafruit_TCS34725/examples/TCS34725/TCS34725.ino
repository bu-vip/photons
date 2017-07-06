// This #include statement was automatically added by the Spark IDE.
#include "Adafruit_TCS34725.h"
#include <math.h>

boolean commonAnode = false;
char szInfo[128];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void setup() {
    Serial.begin(9600);
    Serial.println("Color View Test!");
    
    if (tcs.begin()) {
        Serial.println("Found sensor");
    } else {
        Serial.println("No TCS34725 found ... check your connections");
        while (1); // halt!
    }
}

void loop() {
    uint16_t clear, red, green, blue;

    tcs.setInterrupt(false);      // turn on LED
    
    delay(60);  // takes 50ms to read 
      
    tcs.getRawData(&red, &green, &blue, &clear);
    tcs.setInterrupt(true);  // turn off LED
    
    // Figure out some basic hex code for visualization
    uint32_t sum = clear;
    float r, g, b;
    
    r = red; r /= sum;
    g = green; g /= sum;
    b = blue; b /= sum;
    r *= 256; g *= 256; b *= 256;
    
    sprintf(szInfo, "%d,%d,%d", (int)r, (int)g, (int)b);
    
    Spark.publish("colorinfo", szInfo);
    
    Serial.println(szInfo);
    
    delay(1000);
}
