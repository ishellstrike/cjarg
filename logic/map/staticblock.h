#ifndef STATICBLOCK_H
#define STATICBLOCK_H
#include "logic/map/block.h"
#include "logic/agents/clickreaction.h"
#include <memory>
#include "cereal/cereal.hpp"

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

    int tex[6];
    bool transparent = false;
    std::unique_ptr<ClickReaction> r_click, l_click;
    std::unique_ptr<Block> etalon;

    std::string full_id;
    Jid id;

    bool setTexture(SIDE side, std::string tex_);
    void setTexture(std::string tex_);
    void setSideTexture(std::string tex_);

    void lClick(Block *b);
    void rClick(Block *b);

    void setTexture(Jtex tex_);

    template<class Archive>
    void save(Archive &ar) const
    {
        if(etalon)
            ar(cereal::make_nvp("etalon", *etalon), CEREAL_NVP(transparent), CEREAL_NVP(tex));
    }
};

#endif // STATICBLOCK_H
