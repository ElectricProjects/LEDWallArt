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
long previousMillis = 0; 
long interval = 1500;
byte x = 1;
byte y=0;
int val = 0;
byte z =0;
byte randNumber; 
byte gr=75;
int bl=100;
byte blue= 100;
int dataPin  = 2;
int clockPin = 3;
byte buttonPress=0;

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
int col=8;
int row=8;
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
  blueBack(strip.Color(0, 0, 25),100); // set background to blue
  delay(500);
  sideSwipe();
  delay(500);
  blueBack(strip.Color(0, 0, 25),100); // set background to blue
}


void loop() {

  unsigned long currentMillis = millis();
  int reading = digitalRead(buttonPin);
  if (reading != lastButtonState) {
    //lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        x=2;
        Serial.println("button pushed");       
      }
    }
  }

  switch (x) {
  case 1:
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;  
      r = random(gr); 
      r2 = random(blue);	
      bl++;

      if (bl>=600){
        fadeMix2();
        blueFade(strip.Color(0,r,r2));
        if(bl>=840){
          bl=0;
          sideSwipe2();
          blueBack(strip.Color(0, 0, 25),100); // set background to blue
        }
      }
      if (bl>=400){
        r2 =2;
        blueFade(strip.Color(0,r,r2));
      }
      else if (bl>=200){
        fadeMix();
        blueFade(strip.Color(0,r,r2));
      }
      else {
        r=2;
        blueFade(strip.Color(0,r,r2));
      }
      
    }
    break;

  case 2:
    digitalWrite(buttonPin, HIGH);
    y++;
    heartOutline(strip.Color(127, 0, 0), 50);
    heartOutside(strip.Color(100, 100, 100), 50);
    heartInside(strip.Color(127, 0, 0), 50);
    delay(1000);
    for(int i=0; i<4; i++){
      heartInside(strip.Color(0, 0, 0), 50);
      heartOutline(strip.Color(0, 0, 0), 50);
      delay(500);
      heartInside(strip.Color(127, 0, 0), 50);
      heartOutline(strip.Color(127, 0, 0), 50);
      delay(500);  
    }
    for(int i=0; i<21; i++){
      randomiser(strip.Color(100, 100, 100), 100);
    }

    heartOutline(strip.Color(100, 100, 100), 50);
    heartOutside(strip.Color(125, 0, 0), 50);
    heartInside(strip.Color(100, 100, 100), 50);
    delay(1000);
    for(int i=0; i<4; i++){
      heartInside(strip.Color(0, 0, 0), 50);
      heartOutline(strip.Color(0, 0, 0), 50);
      delay(500);
      heartInside(strip.Color(100, 100, 100), 50);
      heartOutline(strip.Color(100, 100, 1000), 50);
      delay(500);  
    }

    for(int i=0; i<21; i++){
      randomiser(strip.Color(75, 0, 0), 100);
    }

    if (y>=2){
      x=1;
      y=0;
      blueBack(strip.Color(0, 0, 25),100); // set background to blue
    }
    break;
    case 3:
    {
    
    }
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
    Serial.print ("z = ");
    Serial.println(z);
    Serial.print ("Interval = ");
    Serial.println(interval);
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
  Serial.print("interval = ");
  Serial.println(interval);

}

void blueBack(uint32_t c, uint8_t wait) {
  for(int i=0; i<strip.numPixels(); i++)
    strip.setPixelColor(i, c);
  strip.show(); 
}

void valentine(){
  for(int i=0; i<strip.numPixels(); i++){
    strip.setPixelColor(i, 0);
    strip.show();
    delay(10);
  }
  delay(500);

}


void heartOutline(uint32_t c, uint8_t wait){
  for(int i=0; i<13; i++)
  {
    strip.setPixelColor(heartOut[i], (c)); 
    strip.show();
  }
}

void heartOutside(uint32_t c, uint8_t wait){
  for(int i=0; i<30; i++)        
  {
    strip.setPixelColor(heartOuts[i], (c)); 
    strip.show(); 
  }
}

void heartInside(uint32_t c, uint8_t wait){
  for(int i=0; i<21; i++)
  {
    strip.setPixelColor(heartIn[i],(c));
    strip.show();

  }
}

void luv(uint32_t c, uint8_t wait){

  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 0);
    strip.show();

  }

  for(int x=0; x<4; x++){
    strip.setPixelColor(luv1[x],(c));
    strip.show();
    Serial.println("in loop 2");

  }
  delay(wait); 
  delay(1500);
}

void luvL(uint32_t c, uint8_t wait){

  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 0);
    strip.show();

  }

  for(int x=0; x<20; x++){
    strip.setPixelColor(luv2[x],(c));
    strip.show();
    Serial.println("in loop 2");

  }
  delay(wait); 
  delay(1500);
}

void luvU(uint32_t c, uint8_t wait){

  for(int i=0; i<strip.numPixels(); i++)
  {
    strip.setPixelColor(i, 0);
    strip.show();

  }

  for(int x=0; x<7; x++){
    strip.setPixelColor(luv3[x],(c));
    strip.show();
    Serial.println("in loop 2");

  }
  delay(wait); 
  delay(1500);
}

void randomiser(uint32_t c, uint8_t wait){

  randNumber=random(21);
  strip.setPixelColor(heartIn[randNumber],(c));
  strip.show();
  Serial.print("num = ");
  Serial.print(randNumber);
  Serial.print(" ");
  Serial.println(heartIn[randNumber]);
  delay(wait); 
}
void rowFade(uint8_t row){

  for(int i=0; i<8; i++){
    strip.setPixelColor(oneRow[i+row], 0);
    strip.show();
  }
}

void fadeMix(){
  r++;
  if (r>=75)
    r=75;  
}
void fadeMix2(){
  r2++;
  if (r2>=75)
    r2=75;  
}
void sideSwipe(){
byte col = 8;
byte row = 8;

 for (int i = 0; i < row; i++) {
  for (int j = 0; j < col; j++) {
	strip.setPixelColor(myArray[j][i], 0);
  }
  strip.show(); 
  delay(50);
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


