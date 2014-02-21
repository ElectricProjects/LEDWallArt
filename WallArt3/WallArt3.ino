#include "LPD8806.h"
#include "SPI.h"

int nLEDs = 64;
byte buttonPin = 5;

int dataPin  = 2;
int clockPin = 3;
int num = 0;

unsigned long currentMillis=0;
unsigned long previousMillis=0;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

long ledArray[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte arrayCount=0;

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(57600);
  strip.begin();
}

void loop() { 
  currentMillis=millis();
  int r=random(75);
  int r2 = random(50);
  ledRandom(strip.Color(0,r2,r),50);
}

void ledRandom(uint32_t c, uint8_t wait){
 // Serial.println("In Fade2");
  if(currentMillis - previousMillis > wait) {
    previousMillis = currentMillis; 
    do {
      int rand = random(0,63);
      num=rand;
      Serial.print("in do R = ");
      Serial.println(rand);
      Serial.print("count = ");
      Serial.print(arrayCount);
    }
    while (ledArray[num] == 1);
    ledArray[num]=1;
    arrayCount++;
    strip.setPixelColor(num, c); // set rand pixel to new color c
    delay(25);
    strip.show(); // show change in pixel
  }
 /* for(int i =0; i>=64; i++){
    if(ledArray[i] == 1)
      arrayCount++;
  }*/
  if (arrayCount>=63){
     Serial.println("Array 64 +............");
      arrayCount=0;
     for(int i=0; i<=64; i++){
      ledArray[i] = 0;     
    }
    delay(400);
     for (int i=0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0);
      strip.show();
     }
  }
  }

