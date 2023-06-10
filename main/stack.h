#ifndef STACK_H
#define STACK_H

#include <FastLED.h>
#include <list>
#include "block.h"

enum GameState
{
    Idel=0,
    Running=1,
    GameOver=2
};

class stack
{
    public:
        GameState state;
        stack(size_t maxSize, GameState state);
        void calcStep();
        void renderTo(CRGB* leds, size_t size);
        void reset();
        size_t getBlockLengthSum() const;
        void checkForAction(BlockType typeIn);
    protected:
        std::list<block*> blocks;
    private:
        size_t maxSize;
};

#endif /*include guard*/
