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
    StaticBlock(const StaticBlock&) = delete;
    StaticBlock& operator=(const StaticBlock&) = delete;

    int tex[SIDE_AFTER_LAST];
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

    //trivial vars
    bool transparent = false;
    bool cube = true;
    std::string name = "";
    std::string description = "";

    void deserialize(const rapidjson::Value &val)
    {
        DESERIALIZE(NVP(transparent), NVP(cube), NVP(name), NVP(description));

        if(val.HasMember("alltex") || val.HasMember("tex")) {
            if(val.HasMember("alltex")) setTexture(val["alltex"].Begin()->GetString());
            else
            if(val.HasMember("tex")) {
                const rapidjson::Value &arr = val["tex"];
                for(decltype(arr.Size()) a = 0; a < arr.Size(); a++)
                    setTexture(static_cast<StaticBlock::SIDE>(a), arr[a].Begin()->GetString());
            } else
                LOG(error) << "block " << id /*<< " from " << file */<< " has no \"tex\" | \"alltex\"";
        }
    }

    std::string debugInfo()
    {
        std::stringstream s;
        s << DEBUGINFO(transparent);
        s << DEBUGINFO(cube);
        s << DEBUGINFO(name);
        s << DEBUGINFO(description);

        return s.str();
    }
};

#endif // STATICBLOCK_H
