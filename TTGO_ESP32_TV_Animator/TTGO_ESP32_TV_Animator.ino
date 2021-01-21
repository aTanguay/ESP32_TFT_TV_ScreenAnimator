/*
  Animating the screen to look like a little TV screeb for an 'art' project.
  This uses a TTGO ESP32 Module with a nice little screen

  Colors are sent in hex

  This sketch uses the GLCD, 2, 4, 6 fonts only.
 
  Screen resolution for TTGO is 135X240

  Make sure all the display driver and pin comnenctions are correct by
  editting the User_Setup.h file in the TFT_eSPI library folder.

  #########################################################################
  ###### DON'T FORGET TO UPDATE THE User_Setup.h FILE IN THE LIBRARY ######
  #########################################################################
 */

#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

//TFT_eSPI tft = TFT_eSPI();                   // Invoke custom library with default width and height
TFT_eSPI tft = TFT_eSPI(135, 240);       // Could invoke custom library declaring width and height

unsigned long targetTime = 0;
byte red = 31;
byte green = 0;
byte blue = 0;
byte state = 0;
unsigned int colour = red << 11; // Colour order is RGB 5+6+5 bits each
unsigned int var2 = 0;

unsigned long varColor1 = 0x000000;
unsigned long varColor2 = 0xFFFFFF;
unsigned long varColorText = 0x000000;


void setup(void) {
  Serial.begin(9600);
  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  targetTime = millis() + 100;
}





void loop() {

  if (targetTime < millis()) {
    targetTime = millis() + 100;

    //Randomly change the color of the entire screen

    //Choose a color from a range in Hex!
    varColor1 = (random(0xFFFFFF));
    varColorText = (random(0xFFFFFF));

    //Change the color of the screen based on that
    tft.fillScreen(varColor1);

    //Draw a radnom circle on the screen to mess it up
    int rad = random(60);
    int x = rad + random(240 - rad - rad);
    int y = rad + random(135 - rad - rad);
    tft.fillEllipse(x, y, rad, rad, random(0xFFFF));

    

    //Draw the text on top of it. The standard AdaFruit font still works as before
    tft.setCursor(1, 10, 1);        // Set cursor to x = 36, y = 150 and use font 4
    tft.setTextSize(2);             // We are using a size multiplier of 1
    tft.setTextColor(varColorText);    //Probably can use Hex here too
    
    
    
    tft.println("Here's the Color of the screen");  // As we use println, the cursor moves to the next line
    tft.print("   in Hex:");  // As we use println, the cursor moves to the next line
    tft.println(varColor1, HEX);  // As we use println, the cursor moves to the next line

    varColorText = (random(0xFFFFFF));
    tft.setTextColor(varColorText);
    tft.print("   and RGB:");  // As we use println, the cursor moves to the next line
    tft.print(varColor1);  // As we use println, the cursor moves to the next line





    
    Serial.println("Blimey, it works");


    // This Below fades down. The number is n hexx
    //for (int i = 5000; i > 0; i--) 
    //    {
    //    varColor2 = varColor2-1;
    //    tft.println(varColor2, HEX);
    //    tft.fillScreen(varColor2);
    //    delay(30);
    //    }    

    delay(random(100, 3000));

  }
}



void fade()
{
  
}



// Fill screen with a rainbow pattern
void rainbow_fill()
{
  // The colours and state are not initialised so the start colour changes each time the funtion is called
 
  for (int i = 319; i > 0; i--) {
    // Draw a vertical line 1 pixel wide in the selected colour
    tft.drawFastHLine(0, i, tft.width(), colour); // in this example tft.width() returns the pixel width of the display
    // This is a "state machine" that ramps up/down the colour brightnesses in sequence
    switch (state) {
      case 0:
        green ++;
        if (green == 64) {
          green = 63;
          state = 1;
        }
        break;
      case 1:
        red--;
        if (red == 255) {
          red = 0;
          state = 2;
        }
        break;
      case 2:
        blue ++;
        if (blue == 32) {
          blue = 31;
          state = 3;
        }
        break;
      case 3:
        green --;
        if (green == 255) {
          green = 0;
          state = 4;
        }
        break;
      case 4:
        red ++;
        if (red == 32) {
          red = 31;
          state = 5;
        }
        break;
      case 5:
        blue --;
        if (blue == 255) {
          blue = 0;
          state = 0;
        }
        break;
    }
    colour = red << 11 | green << 5 | blue;
  }
}
