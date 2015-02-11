#include "staticblock.h"
#include "sge/textureatlas.h"

StaticBlock::StaticBlock()
{

}

StaticBlock::~StaticBlock()
{

}

void StaticBlock::setTexture(StaticBlock::SIDE side, std::string tex_)
{
    assert(side < SIDE_AFTER_LAST);
    tex[side] = TextureAtlas::refs[tex_];
}

void StaticBlock::setSideTexture(std::string tex_)
{
    tex[SIDE_BACK] = TextureAtlas::refs[tex_];
    tex[SIDE_FRONT] = TextureAtlas::refs[tex_];
    tex[SIDE_LEFT] = TextureAtlas::refs[tex_];
    tex[SIDE_RIGHT] = TextureAtlas::refs[tex_];
}

void StaticBlock::setTexture(Jtex tex_)
{
    for(int i=0; i<SIDE_AFTER_LAST; ++i)
    {
        tex[i] = tex_;
    }
}

void StaticBlock::setTexture(std::string tex_)
{
    for(int i=0; i<SIDE_AFTER_LAST; ++i)
    {
        tex[i] = TextureAtlas::refs[tex_];
    }
}

