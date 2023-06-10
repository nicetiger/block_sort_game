#include <FastLED.h>
#include <list>
#include <algorithm>

// Set our LED Pin to the GPIO Pin
const int ledPin = 2;

#define NUM_LEDS 33

#define DATA_PIN 4
#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];
int TOS = 1;

void setup()
{
  // setup ledPin AS output
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); 
  Serial.begin(115200);
  Serial.println("Starting NimBLE Client");
  initGame();

  // setup input 
  pinMode(25, INPUT_PULLUP);
  pinMode(26, INPUT_PULLUP);
  pinMode(27, INPUT_PULLUP);
}

void initGame(){

  leds[0] = CRGB::Red;
}

class block 
{
  private:
  float pos;
  int len;
  float velocity;
  CRGB color;
  int type;
  public:
    bool active;
    block();
    void update();  
    int getType(){return type;}
    int getLen(){return len;}
};

CRGB typeToColor(int type)
{
  CRGB color = CRGB::Black;
  switch (type)
  {
    case(-1):
    color = CRGB::Black;
  case (0):
    color = CRGB::Red;
    break;
  case (1):
    color = CRGB::Green;
    break;
  case (2):
    color = CRGB::Blue;
    break;
  case (3):
    color = CRGB::Yellow;
    break;
  case (4):
    color = CRGB::Magenta;
    break;
  }
  return color;
}

block::block()
{
  type = int(random()%5);
  pos=NUM_LEDS;

  color=typeToColor(type);
  active=true;
  velocity=(rand()%8)/8.0+0.1;
  len=rand()%4+1;
}

void block::update() 
{
  //Move Block down if not on bottom
  if((pos-velocity) > TOS)
    pos-=velocity;
  else {
   if (active)
   {
        pos=TOS;
    velocity = 0;
    TOS+=len;
    active = false;
  Serial.println(pos);
  Serial.println(TOS);
  Serial.println(active);
  Serial.println("");

   }
  }
  //draw block
  bool first=true;
  for (int p=std::max(1.0f,pos);p<NUM_LEDS && p <= pos+len;p++)
  {
    if (first)
    {
      first=false;
      leds[p]+=color;
    }
    else
      leds[p]+=color%64;
  }
}

std::list<block*> blocks;

void update(int tick)
{
  for (int i=0;i<NUM_LEDS;i++) {
    leds[i]=CRGB::Black;
  }
  if (blocks.size()<1)
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
    
    iter++;
  }
}

int checkTaster(){
  CRGB inputColor;
  int inputType = -1;
  // 0 when pressed
  int taster1 = digitalRead(25); // RED
  int taster2 = digitalRead(26); // GREEN
  int taster3 = digitalRead(27); // BLUE

  if(taster1 == 0){
    inputColor += CRGB::Red;
    inputType += 1;
  }
  if(taster2 == 0){
    inputColor += CRGB::Green; 
    inputType += 2;
  }
  if(taster3 == 0){
    inputColor += CRGB::Blue;
    inputType += 4;
  }
  inputColor = typeToColor(inputType);
  leds[0] = inputColor;
  return inputType;
}

void checkRemoveBlock(int input){
  auto act_block = blocks.front();
  int actType = act_block->getType();
  if(actType == input){
    TOS-=act_block->getLen();
    if(TOS<0)
      TOS=0;
    blocks.remove(act_block);
    delete act_block;
  }
}

bool checkForGameOver(){
  if(TOS >= NUM_LEDS)
  {
    return(true);
  }
  return(false);
}

void resetGame(){
  TOS=1;
    
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

void loop()
{
  int time=millis();

  if (time % 50 == 0)
  {
    if(checkForGameOver()){
      GameOverShow(time/50);
    }
    else
    {
      update(time/50);
      int input = checkTaster();
      checkRemoveBlock(input);    
    }
    FastLED.show();
  }
}
