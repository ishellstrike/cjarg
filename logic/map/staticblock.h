#ifndef STATICBLOCK_H
#define STATICBLOCK_H
#include "logic/map/block.h"

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

    Jtex tex[6] = {0,0,0,0,0,0};
    std::unique_ptr<Block> etalon;

    void setTexture(SIDE side, std::string tex_);
    void setTexture(std::string tex_);
    void setSideTexture(std::string tex_);

    void setTexture(Jtex tex_);
};

#endif // STATICBLOCK_H
