#include "staticblock.h"
#include "sge/textureatlas.h"
#include "sge/logger.h"

StaticBlock::StaticBlock()
{
    for(int i=0; i<6; i++)
    {tex[i] = 0;}
}

StaticBlock::~StaticBlock()
{

}

bool StaticBlock::setTexture(StaticBlock::SIDE side, std::string tex_)
{
    assert(side < SIDE_AFTER_LAST);
    if (TextureAtlas::refs.find(tex_) == TextureAtlas::refs.end())
    {
        LOG(error) << tex_ << " missed";
        tex[side] = TextureAtlas::refs["error"];
        return false;
    }
    tex[side] = TextureAtlas::refs[tex_];
    return true;
}

void StaticBlock::setSideTexture(std::string tex_)
{
    tex[SIDE_BACK] = TextureAtlas::refs[tex_];
    tex[SIDE_FRONT] = TextureAtlas::refs[tex_];
    tex[SIDE_LEFT] = TextureAtlas::refs[tex_];
    tex[SIDE_RIGHT] = TextureAtlas::refs[tex_];
}

void StaticBlock::lClick(Block *b)
{
    if(l_click)
    {
        l_click->Click(b);
    }
}

void StaticBlock::rClick(Block *b)
{
    if(r_click)
    {
        r_click->Click(b);
    }
}

void StaticBlock::setTexture(Jtex tex_)
{
    for(int i=0; i<SIDE_AFTER_LAST; ++i)
    {
        tex[i] = tex_;
    }
}

std::shared_ptr<Block> StaticBlock::instantiate()
{
    if(pure_static)
        return etalon;
    return etalon->instantiate();
}

void StaticBlock::setTexture(std::string tex_)
{
    for(int i=0; i<SIDE_AFTER_LAST; ++i)
    {
        tex[i] = TextureAtlas::refs[tex_];
    }
}

