#ifndef STATICBLOCK_H
#define STATICBLOCK_H
#include "logic/map/block.h"
#include "logic/agents/clickreaction.h"
#include <memory>

class StaticBlock
{
public:
    enum SIDE
    {
        SIDE_TOP,
        SIDE_BOTTOM,
        SIDE_FRONT,
        SIDE_BACK,
        SIDE_LEFT,
        SIDE_RIGHT,
        SIDE_AFTER_LAST
    };

    StaticBlock();
    ~StaticBlock();

    Jtex tex[6];
    bool transparent = false;
    std::unique_ptr<ClickReaction> r_click, l_click;
    std::unique_ptr<Block> etalon;

    void setTexture(SIDE side, std::string tex_);
    void setTexture(std::string tex_);
    void setSideTexture(std::string tex_);

    void lClick(Block *b);
    void rClick(Block *b);

    void setTexture(Jtex tex_);
};

#endif // STATICBLOCK_H
