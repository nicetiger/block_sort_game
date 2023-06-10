#ifndef BLOCK_H
#define BLOCK_H

#include <FastLED.h>

enum BlockType
{
    Random=0,
    ColorRed=1,
    ColorGreen=2,
    ColorBlue=3,
    ColorYellow=4,
    ColorMagenta=5,
    ColorTurquoise=6,
    
    /*keepAtEnd*/BLOCKTYPE_MAX
};

class block 
{
  private:
    float pos;
    size_t len;
    float velocity;
    BlockType type;
  public:
    block(float pos,BlockType type=BlockType::Random);
    static CRGB typeToColor(BlockType type);
    void renderTo(CRGB* leds, size_t size);

    BlockType getType() const {return type;}
    size_t getLen() const {return len;}
    void setLen(size_t lenNew) {len=lenNew;}
    void setPos(float fNew) {this->pos=fNew;}
    float getPos() const {return pos;}
    float getVelocity() const {return velocity;}
};

#endif /*include guard*/

