#include "fatal.h"
#include "sge/logger.h"

void Organ::deserialize(rapidjson::Value &val)
{
    if(val.HasMember("buffs") && val["buffs"].IsArray())
    {
        rapidjson::Value &b = val["buffs"];
        for(int i = 0; i < b.Size(); i++)
            buffs.push_back(val[i].GetString());
    }
    LOG(verbose) << "organ with buffs " << buffs.size();
}

Agent *Organ::instantiate() const
{
    Agent *f = new Organ;
    return f;
}

void Organ::Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l)
{

}

void Organ::Init(const glm::vec3 &pos, const Level &l)
{

}
