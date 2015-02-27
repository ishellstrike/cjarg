#ifndef CLICKREACTION_H
#define CLICKREACTION_H
#include "logic/map/block.h"

struct ClickReaction
{
    virtual void Click(Block *b) = 0;
};

struct ClickReactionTest : public ClickReaction
{
    void Click(Block *b);
};

#endif // CLICKREACTION_H
