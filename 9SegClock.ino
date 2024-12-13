/* 
Code by Sacha Silvia
Credits to Rui Santos for original Date and Time retrieval from an NTP Server
  L_> https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
For 9-Segment LED Clock 
*/ 

/* Map
0  -  0    0  -  0    x    0  -  0    0  -  0
|  x  |    |  x  |    |    |  x  |    |  x  | 
0  -  0    0  -  0    x    0  -  0    0  -  0
|  x  |    |  x  |    |    |  x  |    |  x  |
0  -  0    0  -  0    x    0  -  0    0  -  0

4  5 14   15 24 25   34   35 44 45   54 55 64
3  6 13   16 23 26   33   36 43 46   53 56 63
2  7 12   17 22 27   32   37 42 47   52 57 62
1  8 11   18 21 28   31   38 41 48   51 58 61
0  9 10   19 20 29   30   39 40 49   50 59 60
*/
// Import Libraires 
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>

// Define param values
#define EST -18000 // Offset from GMT (sec)
#define updateFrequency // Time check delay 
#define PIN GPIO13 // Set NPXL to ESP pin
#define NUMPIXELS 0 // Total LEDs

// Declare gloabal vars
byte H; // Store hours
byte M; // Store minutes

// Initialize global vars
const char* ssid = "Shelby"; // Router SSID
const char* password = "80138013"; // Router password
const long utcOffsetInSeconds = EST; // Set Timezone
const int GPIO13 = 13;
bool high = true;
bool low = false;

// Create objects (sourced from libs)
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds); // Time Getter
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800); // NPXL

/*
This method identifies a given range of LEDs and turns them on or off (inclusive)
Call the function via: setled(int,int,bool);
*/
void setled(int start, int end, bool hiLo) {
  for (int pixel = 0; pixel < numPixels; pixel++){
    if(hiLow == high){
      pixels.setPixelColor(pixel, pixels.Color(255, 255, 255));
    }
    else{
      pixels.setPixelColor(pixel, pixels.Color(0, 0, 0));
    }
    pixels.show();
  }
}

// This method runs once 
void setup() {
  Serial.begin(115200); // Start console at needed baud rate
  Serial.println("Establishing connection with: " + ssid);
  WiFi.begin(ssid, password); // Start WiFi 
  // Loop until connection
  while (WiFi.status != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Successfully connected to: " + ssid);
  timeClinet.begin(); // Get time 
  pixels.begin(); // Create pixels
  pixels.clear(); // Wipe pixel data
}

// This method is an inf. loop
void loop() {
  timeClient.update(); // Re-check time
  // Set (and reset) time to vars
  H = timeClient.getHours();
  M = timeClient.getMinutes();
  /* 
  For Devs
  Check time in console
  Compare to hardware or test without hardware
  Section can be commented out if not testing
  */
  // /*
  Serial.println("");
  Serial.println("Hour: " + H);
  Serial.println("Minute: " + M);
  // */

  // Time check update speed
  delay(updateFrequency);
}
