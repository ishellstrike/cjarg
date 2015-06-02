#include "furnance.h"

Agent *Furnance::instantiate() const
{
    return nullptr;
}

void Furnance::deserialize(rapidjson::Value &val)
{
    if(val.HasMember("temp"))
    {
        temp = val["temp"].GetInt();
    }
}

void Furnance::Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner)
{

}

void Furnance::Init(const glm::vec3 &pos, const Level &l)
{

}
