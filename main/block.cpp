#include "block.h"

block::block(float fStart, BlockType typeStart): pos(fStart), type(typeStart)
{
  if(type==Random) {
      type = BlockType(random()%(BLOCKTYPE_MAX-1)+1);
  }
  velocity=(rand()%8)/8.0+0.1;
  len=rand()%4+1;
}

CRGB block::typeToColor(BlockType type)
{
  CRGB color;
  switch (type)
  {
  case (ColorRed):
    color = CRGB::Red;
    break;
  case (ColorGreen):
    color = CRGB::Green;
    break;
  case (ColorBlue):
    color = CRGB::Blue;
    break;
  case (ColorYellow):
    color = CRGB::Yellow;
    break;
  case (ColorMagenta):
    color = CRGB::Magenta;
    break;
  case (ColorTurquoise):
    color = CRGB::DarkTurquoise;
    break;
    
  default:
    color = 0x040404; /*something's wrong!*/
  }
  return color;
}

void block::renderTo(CRGB* leds, size_t size) {
  CRGB color=typeToColor(type);
  
  for(size_t u=0;u<len;++u){
    size_t uL=ceil(pos)+u;
    if(uL<size) {
      leds[uL]=color;
    }
  }
}

