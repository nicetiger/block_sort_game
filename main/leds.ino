#include <FastLED.h>
#include <list>

// Set our LED Pin to the GPIO Pin
const int ledPin = 2;

#define NUM_LEDS 33

#define DATA_PIN 4
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

void setup()
{
  // setup ledPin AS output
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");
  initGame();
}

void initGame(){

  leds[0] = CRGB::Red;
}

class block 
{
  private:
  int pos;
  int len;
  int velocity;
  CRGB color;
  public:
    bool active;
    block();
    void update();  
};

block::block()
{
  Serial.println("new block");
  pos=NUM_LEDS;
  color=CRGB::Red;
  active=true;
  velocity=rand()%4+1;
  len=rand()%4+1;
}

void block::update() 
{
  Serial.println(pos); 
  if (!active) return;
  pos-=velocity;
  if (pos<0)
    active=false;
  else
  {
    //draw block
    for (int p=pos;p<NUM_LEDS && p < pos+len;p++)
      leds[p]=color;
  }
}

std::list<block*> blocks;

void update(int tick)
{
  for (int i=0;i<NUM_LEDS;i++) {
    leds[i]=CRGB::Black;
  }
  if (blocks.size()<5)
  {
    auto b = new block();
    blocks.push_back(b);
  }
  auto iter = blocks.begin();
  auto end  = blocks.end();

  while (iter != end)
  {
    auto b=*iter;
    b->update();
    if (!b->active)
    {
      iter=blocks.erase(iter);
      delete b;
    }
    iter++;
  }
}

void loop()
{
  int time=millis();

  if (time % 50 == 0)
  {
    update(time/50);
    FastLED.show();
  }
}
