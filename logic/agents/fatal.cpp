#include "fatal.h"

void Organ::deserialize(rapidjson::Value &val)
{
    if(val.HasMember("buff_id"))
        buff_id = val["items"].GetString();
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
