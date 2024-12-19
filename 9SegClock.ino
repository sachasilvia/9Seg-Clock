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
#define EST -18000            // Offset from GMT (sec)
#define updateFrequency 1000  // Time check delay
#define PIN GPIO13            // Set NPXL to ESP pin
#define NUMPIXELS 0           // Total LEDs

// Declare gloabal vars
int h;  // Store hours
int m;  // Store minutes

// Initialize global vars
const char* ssid = "Shelby";          // Router SSID
const char* password = "80138013";    // Router password
const long utcOffsetInSeconds = EST;  // Set Timezone
const int GPIO13 = 13;
bool high = true;
bool low = false;

// Create objects (sourced from libs)
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);  // Time Getter
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);    // NPXL

/*
This method identifies a given range of LEDs and turns them on or off (inclusive)
Call the function via: setLed(int,int,bool);
*/
void setLed(int sStart, int sEnd) {
  for (int sPixel = sStart; sPixel <= sEnd; sPixel++) {
    pixels.setPixelColor(sPixel, pixels.Color(245, 245, 220));
  }
  pixels.show();
}

void clearLed(int cStart, int cEnd) {
  for (int cPixel = cStart; cPixel <= cEnd; cPixel++) {
    pixels.setPixelColor(cPixel, pixels.Color(0xFF, 0xFF, 0xFF));
  }
  pixels.show();
}

void clearFace(int face) {
  if      (face == 1) {clearLed(0, 14);}
  else if (face == 2) {clearLed(15, 29);}
  else if (face == 3) {clearLed(35, 49);}
  else if (face == 4) {clearLed(50, 64);}
}

void drawColon() {
  setLed(33, 33);
  setLed(31, 31);
}

void drawZero(int zeroFace) {  //1-4
  clearFace(zeroFace);
  if (zeroFace == 1) {
    setLed(0, 5);
    setLed(9, 14);
  } else if (zeroFace == 2) {
    setLed(15, 20);
    setLed(24, 29);
  } else if (zeroFace == 3) {
    setLed(35, 40);
    setLed(44, 49);
  } else if (zeroFace == 4) {
    setLed(50, 55);
    setLed(59, 60);
  }
}

void drawOne(int oneFace) {  //1-4
  clearFace(oneFace);
  if      (oneFace == 1) {setLed(10, 14);} 
  else if (oneFace == 2) {setLed(25, 29);}
  else if (oneFace == 3) {setLed(45, 49);}
  else if (oneFace == 4) {setLed(60, 64);}
}

void drawTwo(int twoFace) {  //2-4
  clearFace(twoFace);
  if (twoFace == 2) {
    setLed(15, 15);
    setLed(24, 27);
    setLed(22, 22);
    setLed(17, 20);
    setLed(29, 29);
  } else if (twoFace == 3) {
    setLed(35, 35);
    setLed(44, 47);
    setLed(42, 42);
    setLed(37, 40);
    setLed(49, 49);
  } else if (twoFace == 4) {
    setLed(54, 55);
    setLed(62, 64);
    setLed(57, 57);
    setLed(50, 52);
    setLed(59, 60);
  }
}

void drawThree(int threeFace) {  //2-4
  clearFace(threeFace);
  if (threeFace == 2) {
    setLed(15, 15);
    setLed(24, 29);
    setLed(17, 17);
    setLed(22, 22);
    setLed(19, 20);
  } else if (threeFace == 3) {
    setLed(35, 35);
    setLed(44, 49);
    setLed(37, 37);
    setLed(42, 42);
    setLed(39, 40);
  } else if (threeFace == 4) {
    setLed(54, 55);
    setLed(64, 59);
    setLed(57, 57);
    setLed(52, 52);
    setLed(50, 50);
  }
}

void drawFour(int fourFace) {
  clearFace(fourFace);
  if (fourFace == 2) {
    setLed(15, 17);
    setLed(25, 29);
    setLed(22, 22);
  } else if (fourFace == 3) {
    setLed(35, 37);
    setLed(45, 49);
    setLed(42, 42);
  } else if (fourFace == 4) {
    setLed(52, 54);
    setLed(60, 64);
    setLed(57, 57);
  }
}

void drawFive(int fiveFace) {
  clearFace(fiveFace);
  if (fiveFace == 2) {
    setLed(24, 25);
    setLed(15, 17);
    setLed(22, 22);
    setLed(27, 29);
    setLed(19, 20);
  } else if (fiveFace == 3) {
    setLed(44, 45);
    setLed(35, 37);
    setLed(42, 42);
    setLed(47, 49);
    setLed(39, 40);
  } else if (fiveFace == 4) {
    setLed(64, 64);
    setLed(52, 55);
    setLed(57, 57);
    setLed(59, 62);
    setLed(50, 50);
  }
}

void drawSix(int sixFace) {
  clearFace(sixFace);
  if (sixFace == 2) {
    setLed(15, 20);
    setLed(24, 25);
    setLed(27, 29);
    setLed(22, 22);
  } else if (sixFace == 3) {
    setLed(35, 40);
    setLed(44, 45);
    setLed(47, 49);
    setLed(42, 42);
  } else if (sixFace == 4) {
    setLed(50, 55);
    setLed(64, 64);
    setLed(59, 62);
    setLed(57, 57);
  }
}

void drawSeven(int sevenFace) {
  clearFace(sevenFace);
  if (sevenFace == 2) {
    setLed(24, 29);
    setLed(15, 16);
  } else if (sevenFace == 3) {
    setLed(44, 49);
    setLed(35, 36);
  } else if (sevenFace == 4) {
    setLed(53, 55);
    setLed(60, 64);
  }
}

void drawEight(int eightFace) {
  clearFace(eightFace);
  if (eightFace == 2) {
    setLed(15, 20);
    setLed(24, 29);
    setLed(22, 22);
  } else if (eightFace == 3) {
    setLed(35, 40);
    setLed(44, 49);
    setLed(42, 42);
  } else if (eightFace == 4) {
    setLed(50, 55);
    setLed(59, 64);
    setLed(57, 57);
  }
}

void drawNine(int nineFace) {
  clearFace(nineFace);
  if (nineFace == 2) {
    setLed(15, 17);
    setLed(24, 29);
    setLed(22, 22);
  } else if (nineFace == 3) {
    setLed(35, 37);
    setLed(44, 49);
    setLed(42, 42);
  } else if (nineFace == 4) {
    setLed(52, 55);
    setLed(60, 64);
    setLed(57, 57);
  }
}
// This method runs once
void setup() {
  Serial.begin(115200);  // Start console at needed baud rate
  Serial.print("Establishing connection with: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  // Start WiFi
  // Loop until connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Successfully connected to: ");
  Serial.println(ssid);
  timeClient.begin();  // Get time
  pixels.begin();      // Create pixels
  pixels.clear();      // Wipe pixel data
  drawColon();
}

// This method is an inf. loop
void loop() {
  timeClient.update();  // Re-check time
  // Set (and reset) time to vars
  h = timeClient.getHours();
  m = timeClient.getMinutes();
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

  // if newH != h...
  if ((h > 0 && h < 10) || (h > 12 && < 22)) {drawZero(1);}
  else {drawOne(1);}
  
  if      (h == 1 || h == 13) {drawOne(2);} 
  else if (h == 2 || h == 14) {drawTwo(2);} 
  else if (h == 3 || h == 15) {drawThree(2);} 
  else if (h == 4 || h == 16) {drawFour(2);} 
  else if (h == 5 || h == 17) {drawFive(2);} 
  else if (h == 6 || h == 18) {drawSix(2);} 
  else if (h == 7 || h == 19) {drawSeven(2);} 
  else if (h == 8 || h == 20) {drawEight(2);} 
  else if (h == 9 || h == 21) {drawNine(2);} 
  else if (h == 10 || h == 22) {drawZero(2);} 
  else if (h == 11 || h == 23) {drawOne(2);} 
  else if (h == 12 || h == 0) {drawTwo(2);}

  //if newM != m...
  if      (m < 10){drawZero(3);}
  if      (m == 0){drawZero(4);}
  else if (m == 1){drawOne(4);}
  else if (m == 2){drawTwo(4);}
  else if (m == 3){drawThree(4);}
  else if (m == 4){drawFour(4);}
  else if (m == 5){drawFive(4);}
  else if (m == 6){drawSix(4);}
  else if (m == 7){drawSeven(4);}
  else if (m == 8){drawEight(4);}
  else if (m == 9){drawNine(4);}

  // Time check update speed
  delay(updateFrequency);
}
