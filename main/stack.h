#ifndef STACK_H
#define STACK_H

#include <FastLED.h>
#include <list>
#include "block.h"

class stack
{
    public:
        explicit stack(size_t maxSize);
        void calcStep();
        void renderTo(CRGB* leds, size_t size);
        size_t getBlockLengthSum() const;
    protected:
        std::list<block*> blocks;
    private:
        size_t maxSize;
};

#endif /*include guard*/
