#include <Adafruit_NeoPixel.h> //library developed by Adafruit.
#include <LiquidCrystal.h>    //include the LCD library

#define PIN 2  //pin 2 is connected to RainbowBit's Input pin.

#define LED  13  //LED on Arduino
#define BitNumber  4  //number of RainbowBit

// Parameter 1 = number of RainbowBit in strip
// Parameter 2 = pin number connected to RainbowBit's input (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
Adafruit_NeoPixel strip = Adafruit_NeoPixel(BitNumber, PIN, NEO_GRB + NEO_KHZ800);

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);  //LCD is meant for BBFuino or LCD keypad shield.

void setup() {
  lcd.begin(8,2);  //initialize LCD
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);
  
  strip.begin();  //initialize register needed for RainbowBit
  delay(100);
  
  strip.show();             // Initialize all RainbowBits to 'off'
  lcd.print("RainbowB");
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Examples");
  delay(500);
}

void loop() {   
  lcd.clear();  //clear LCD
  lcd.print("Color:");
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Red  ");
  digitalWrite(LED, HIGH);
  delay(10);
  // Some example procedures showing how to display to the Dot:
  colorWipe(strip.Color(255, 0, 0), 100); // Red
  delay(100);
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Green");
  colorWipe_R(strip.Color(0, 255, 0), 100); // Green
  delay(100);
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Blue ");
  colorWipe(strip.Color(0, 0, 255), 100); // Blue
  delay(100);
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("White");
  colorWipe_R(strip.Color(255, 255, 255), 100); // White
  delay(100);
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Blank");
  colorWipe(strip.Color(0, 0, 0), 100); // OFF
  delay(100);
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Mix! ");
  rainbow(20);
  rainbowCycle(20);
  delay(100);
  lcd.clear();
  lcd.print("Done");
  lcd.setCursor(0, 1);  //2nd line
  lcd.print("Repeat");
  delay(1000);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}

void colorWipe_R(uint32_t c, uint8_t wait) {
  for(uint16_t i=strip.numPixels(); i>0; i--) {
      strip.setPixelColor(i-1, c);
      strip.show();
      delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i+j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
    for(i=0; i< strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}
