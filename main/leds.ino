#include <FastLED.h>
#include <algorithm>

#include "stack.h"
#include "block.h"


// Set our LED Pin to the GPIO Pin
const int ledPin = 2;

#define NUM_LEDS 33

#define DATA_PIN 4
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

stack s(NUM_LEDS-1);


void setup()
{
  // setup ledPin AS output
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  Serial.begin(115200);
  Serial.println("Starting BlockSortGame");
  initGame();

  // setup input 
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
}

void initGame()
{
  leds[0] = CRGB::Blue;
  FastLED.show();
  usleep(3000);
  leds[0] = CRGB::Red;
  FastLED.show();
}

void update(int tick)
{
  for (int i=0;i<NUM_LEDS;i++) {
    leds[i]=CRGB::Black;
  }
  s.calcStep();
  s.renderTo(leds+1,NUM_LEDS-1);
  
  
}
/*
int checkTaster(){
  CRGB inputColor;
  int inputType = 0;
  // 0 when pressed
  int taster1 = digitalRead(25); // RED
  int taster2 = digitalRead(26); // GREEN
  int taster3 = digitalRead(27); // BLUE

  if(taster1 == 0){
    inputType += 1;
  }
  if(taster2 == 0){
    inputType += 2;
  }
  if(taster3 == 0){
    inputType += 4;
  }
  inputColor = typeToColor(inputType);
  leds[0] = inputColor;
  return inputType;
}
*/


/*bool checkForGameOver(){
  if(TOS >= NUM_LEDS)
  {
    return(true);
  }
  return(false);
}

void resetGame(){
  //Del all Block from List
  auto iter = blocks.begin();
  auto end  = blocks.end();
  while (iter != end)
  {
    auto b=*iter;
    iter=blocks.erase(iter);
    delete b;
    iter++;
  }
}

void GameOverShow(int time)
{ 
  for (int i=0;i<NUM_LEDS;i++) {
    leds[i]=CRGB::Red;
  }
  static int oldtime = 0;
  if(oldtime == 0)
    oldtime = time;
  if(time-oldtime > 3000/50) {
    resetGame();
    oldtime = 0;
  }

}
*/

void loop()
{
  int time=millis();

  if (time % 50 == 0)
  {/*
    if(checkForGameOver()){
      GameOverShow(time/50);
    }
    else
    {*/
      update(time/50);
 //     int input = checkTaster();
 //     checkRemoveBlock(input);    
    /*}*/
    FastLED.show();
  }
}
