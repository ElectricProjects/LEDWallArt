#include "LPD8806.h"

#include "SPI.h"

int nLEDs = 64;
byte buttonPin = 5;
int buttonState;             // the current reading from the input pin
int lastButtonState = HIGH;   // the previous reading from the input pin
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;
byte r; //random color
byte r2;  //random color 2
byte rLed; // random led
int prevLed=0;

byte buttonPresses=1;

byte z =0;
byte randNumber; 
int counter=100;

int dataPin  = 2;
int clockPin = 3;
byte buttonPress=0;
byte yellow=0;
byte green=0;
byte blue=0;

byte col = 8;
byte row = 8;

unsigned long currentMillis = millis();
long previousMillis = 0; 
long interval = 1500;
long previousMillisSwipe = 0;
long intervalSwipe = 400;

LPD8806 strip = LPD8806(nLEDs, dataPin, clockPin);

unsigned long heartOut[] = {
  3,11,13,17,21,25,31,32,38,41,47,49,53};
unsigned long heartOuts[] = {
  0,1,2,4,5,6,7,8,9,10,14,15,16,22,23,24,39,40,48,51,54,55,56,57,58,59,60,61,62,63};
unsigned long heartIn[] = {
  12,18,19,20,26,27,28,29,30,33,34,35,36,37,42,43,44,45,46,50,52};
unsigned long luv1[] = {
  13,18,29,45};
unsigned long luv2[] = {
  0,1,2,3,15,16,18,19,20,27,29,31,32,34,36,42,52,54,56,60};
unsigned long luv3[] = {
  18,19,20,27,29,34,36};

unsigned long oneRow[] = {
  0,1,2,3,4,5,6,7};

int myArray[8][8]  = { 
  {0, 1, 2, 3,4,5,6,7},
  {8,9,10,11,12,13,14,15},
  {16,17,18,19,20,21,22,23},
  {24,25,26,27,28,29,30,31},
  {32,33,34,35,36,37,38,39},
  {40,41,42,43,44,45,46,47},
  {48,49,50,51,52,53,54,55},
  {56,57,58,59,60,61,62,63}		
};
int myArray2[8][8]  = { 
  {0, 1, 2, 3,4,5,6,7},
  {15,14,13,12,11,10,9,8},
  {16,17,18,19,20,21,22,23},
  {31,30,29,28,27,26,25,24},
  {32,33,34,35,36,37,38,39},
  {47,46,45,44,43,42,41,40},
  {48,49,50,51,52,53,54,55},
  {63,62,61,60,59,58,57,56}		
};

void setup() {
  randomSeed(analogRead(0));
  Serial.begin(57600);
  strip.begin();
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);  
  solidBack(strip.Color(0, 0, 25),100); // set background to blue
  delay(500);
  sideSwipe();
  delay(500);
  solidBack(strip.Color(0, 0, 25),100); // set background to blue
}


void loop() {
   currentMillis = millis();
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    //lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        buttonPresses++;
        if (buttonPresses>=4)
        buttonPresses=1;
        Serial.println("button pushed");       
      }
    }
  }

  switch (buttonPresses) {
  case 1:
        green= random(10, 100); 
        blue = random(10, 100);	
        yellow =0;
        Serial.println("Case 1");
        fade();
    break;

  case 2:
    Serial.println("Case 2");
    swipeRight();
    //sideSwipe2();
     solidBack(strip.Color(0, 0, 25),100);
    sideSwipe3();
     solidBack(strip.Color(0, 0, 25),100);
    break;
    case 3:
        Serial.println("Case 3");
        green= 0; 
        blue = random(10, 100);	
        yellow = random(10, 100);
        fade();
    break;
  }
}

void blueFade(uint32_t c) {
  rLed = random(63); 
  do{         
    rLed = random(63); 
  } 
  while (rLed == prevLed);
  prevLed= rLed; 
  strip.setPixelColor(rLed, c); 
  strip.show(); 

  if (interval<=0){
    z++;
    interval=5;
    if (z>=150){
      interval=1500;
      z=0;
    }
  }
  else
    if(interval<=50){
      interval-=1;
    }
    else
      if (interval <75)
        interval-=2;
      else
        if
          (interval<=500)
          interval-=25;
      else
        interval -=50;
}

void solidBack(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++)
    strip.setPixelColor(i, c);
  strip.show(); 
}
void rowFade(uint8_t row){

  for(int i=0; i<8; i++){
    strip.setPixelColor(oneRow[i+row], 0);
    strip.show();
  }
}

void sideSwipe(){
byte col = 8;
byte row = 8;

 for (int i = 0; i < row; i++) {
  for (int j = 0; j < col; j++) {
	strip.setPixelColor(myArray[j][i], 0);
  }
  strip.show(); 
  delay(40);
  }
}

void fade(){
   Serial.println("In Fade");
   if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;  
      counter++;
      if (counter>=600){
        green++;
        if (green>=75)
        green=75;     
        blueFade(strip.Color(yellow,green,blue));
        if(counter>=840){
          counter=0;
          swipeRight();
          solidBack(strip.Color(yellow,green,blue),100); // set background to blue
        }
      }
      if (counter>=400){
        blue =2;
        blueFade(strip.Color(yellow,green,blue));
      }
      else if (counter>=200){
           blue++;
           if (blue>=75)
           blue=75;  
           blueFade(strip.Color(yellow,green,blue));
      }
      else {
       green=2;
       blueFade(strip.Color(yellow,green,blue));
      }
      Serial.print("Fade counter = ");
      Serial.println(counter);
    }
  
}

void swipeRight(){
 for (int i = 0; i < row; i++) {
   if(currentMillis - previousMillisSwipe > intervalSwipe) {
      previousMillisSwipe = currentMillis; 
      for (int j = 0; j < col; j++) {
	strip.setPixelColor(myArray2[j][i], 0);
  } 
      strip.show(); 
  }  
 }
 solidBack(strip.Color(0, 0, 25),100);
}

void swipeLeft(){
  if(currentMillis - previousMillisSwipe > intervalSwipe) {
      previousMillisSwipe = currentMillis; 
 for (int i = row; i <=0; i--) {
  for (int j = col; j <=0; j--) {
	strip.setPixelColor(myArray2[j][i], 0);
  } 
  }
  }
}


void sideSwipe2(){
byte col = 8;
byte row = 8;

 for (int i = 0; i < row; i++) {
  for (int j = 0; j < col; j++) {
	strip.setPixelColor(myArray2[j][i], 0);
  }
  strip.show(); 
  delay(40);
  }
  
}

void sideSwipe3(){

 for (int i = row; i <= 0; i--) {
  for (int j = col; j <=0; j--) {
	strip.setPixelColor(myArray2[j][i], 0);
  }
  strip.show(); 
  delay(40);
  }
  
}
