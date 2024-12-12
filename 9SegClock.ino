/* 
Code by Sacha Silvia
Credits to Rui Santos for original Date and Time retrieval from an NTP Server
  L_> https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/
For 9-Segment LED Clock 
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
