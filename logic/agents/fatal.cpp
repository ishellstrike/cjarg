#include "fatal.h"
#include "sge/logger.h"
#include "sge/helper.h"
#include <sstream>
#include "gamepart.h"

void Organ::deserialize(rapidjson::Value &val)
{
    if(val.HasMember("buffs"))
    {
        if(val["buffs"].IsArray()) {
            rapidjson::Value &b = val["buffs"];
            for(int i = 0; i < b.Size(); i++)
                buffs.push_back(b[i].GetString());
        } else {
            LOG(error) << "\"Organ\" buffs must be array";
        }
    }

    DESERIALIZE(health);
    DESERIALIZE(material);
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
