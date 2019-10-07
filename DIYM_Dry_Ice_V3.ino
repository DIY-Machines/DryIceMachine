/*
 * Remote controlled bluetooth Dry Ice Machine - DIY Machines

This is an easy to build dry ice fog machine. It's controlled by an Arduino Nano over a bluetooth connection from your smartphone. It also inlcudes LED lighting effects.

==========

More info: https://diymachines.co.uk/

3D printed parts can be downloaded from here: https://www.thingiverse.com/thing:

==========


 * SAY THANKS:

Buy me a coffee to say thanks: https://ko-fi.com/diymachines
Support us on Patreon: https://www.patreon.com/diymachines

SUBSCRIBE:
■ https://www.youtube.com/channel/UC3jc4X-kEq-dEDYhQ8QoYnQ?sub_confirmation=1

INSTAGRAM: https://www.instagram.com/diy_machines/?hl=en
FACEBOOK: https://www.facebook.com/diymachines/

*/

#include <Adafruit_NeoPixel.h>

//Motor Pins
int EN_A = 11;      //Enable pin for motor
int IN1 = 9;       //control pin for motor
int IN2 = 8;       //control pin for motor


//limit switches
int lowerLimit = 3;             //pin for contact switch limiting downward movement
int upperLimit = 4;             //pin for contact switch limiting upwards movement
int lowerLimitValue = 0;       //somewhere to store the value of the switch limiting downward movement
int upperLimitValue = 0;       //somewhere to store the value of the switch limiting upward movement

char command;


//LED lights (if you're using them)
#define PIXEL_PIN    6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 12  // Number of NeoPixels

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

boolean oldState = HIGH;
int     mode     = 0;    // Currently-active animation mode, 0-5


void setup ( ) {
  Serial.begin (9600); //Starting the serial communication at 9600 baud rate

  
  //Initializing the motor pins as output
  pinMode(EN_A, OUTPUT);
  pinMode(IN1, OUTPUT);  
  pinMode(IN2, OUTPUT);

  //configure the button pins
  pinMode(lowerLimit, INPUT);
  pinMode(upperLimit, INPUT);
  pinMode(lowerLimit, INPUT_PULLUP);
  pinMode(upperLimit, INPUT_PULLUP);

  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
                
}

void loop () {


    
  if(Serial.available() > 0){ 
      command = Serial.read(); 
      wait(); //initialize with motors stopped   
      Serial.println(command);
      
      switch(command){
                      case 'D':  
                        down();
                        break;
                      case 'U':  
                         up();
                        break;
                      case 'R':  
                         redLED();
                        break;
                      case 'G':  
                         greenLED();
                        break;
                      case 'B':  
                         blueLED();
                        break;
                      case 'O':  
                         offLED();
                        break;
                      case 'W':  
                         whiteLED();
                        break;
                      case 'S':  
                         sparkleLED();
                        break;
                      default:
                        wait();
                        break;
        }
    }



 
}

 void down()
  { 
    for (int i = 0; i <= 50; i++) {
          lowerLimitValue = digitalRead(lowerLimit);
          Serial.println(lowerLimitValue);
        if (lowerLimitValue != 0) {
              digitalWrite(IN1, LOW);
              digitalWrite(IN2, HIGH);
              analogWrite(EN_A, 255);
              delay(5);
        }
        else{
          break;
        }    
     }
  }


   void up()
  { 
    for (int i = 0; i <= 50; i++) {
          upperLimitValue = digitalRead(upperLimit);
          Serial.println(upperLimitValue);
        if (upperLimitValue != 0) {
              digitalWrite(IN1, HIGH);
              digitalWrite(IN2, LOW);
              analogWrite(EN_A, 255);
              delay(5);
        }
        else{
          break;
        }    
     }
  }
  
  
 void wait()
  {
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, LOW);
  }


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}

void redLED(){
  colorWipe(strip.Color(150,   0,   0), 50);    // Red
}

void greenLED(){
  colorWipe(strip.Color(0,   150,   0), 50);    // Green
}

void blueLED(){
  colorWipe(strip.Color(0,   0,   150), 50);    // Blue
}

void whiteLED(){
  colorWipe(strip.Color(150,   150,   150), 50);    // White
}

void offLED(){
  colorWipe(strip.Color(0,   0,   0), 50);    // Off
}

void sparkleLED(){
  theaterChase(strip.Color(150, 150, 150), 300); // Sparkle white
}
  
