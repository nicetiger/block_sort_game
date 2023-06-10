#include "stack.h"
        
stack::stack(size_t maxSize): maxSize(maxSize) {
  block *b=new block(maxSize);
  blocks.push_back(b);
}

void stack::calcStep() {
  float fUpperPos=0.0;

  auto iter = blocks.begin();
  auto end  = blocks.end();

  while (iter != end)
  {
//    Serial.println(fUpperPos);
    auto b=*iter;
    float tmpPos = b->getPos() - b->getVelocity();

    if(tmpPos > fUpperPos) {
      b->setPos(tmpPos);
    } else {
      b->setPos(fUpperPos);
      /*TODO: Adapt velocity of this and pre block (if any)*/
    }
    fUpperPos=b->getPos()+b->getLen();
    iter++;
  }
  
  /*ToDo: Move out of here, put to game loop, make level-dependent*/
  if(random8()>250) {
      block *b=new block(maxSize);
      blocks.push_back(b);
      
  }
}

void stack::renderTo(CRGB* leds, size_t size) {
    
  auto iter = blocks.begin();
  auto end  = blocks.end();

  while (iter != end)
  {
    auto b=*iter;
    b->renderTo(leds,size);
    iter++;
  }
}

size_t stack::getBlockLengthSum() const {
  size_t retSize=0;
  std::list<block*>::const_iterator cit;
    for (cit = blocks.begin(); cit != blocks.end(); ++cit){
        retSize+=(*cit)->getLen();
    }
  return retSize;
}

void stack::checkForAction(BlockType typeIn) {
    if(blocks.size()) {
      block* b=*(blocks.begin());
      if(b->getPos()<1) {
        /*there is a block, waiting to be triggerd*/
        if(b->getType()==typeIn){
          if(b->getLen()>1) {
            b->setPos(b->getPos()+1.0);
            b->setLen(b->getLen()-1);
          } else {
            blocks.pop_front();
            delete b;
          }
        }
      }
    }
}

/*
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
}*/
