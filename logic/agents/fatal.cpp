#include "fatal.h"
#include "sge/logger.h"
#include "sge/helper.h"
#include <sstream>

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

    health = val.HasMember("health") ? val["health"].GetInt() : 1;
    material = val.HasMember("material") ? val["material"].GetString() : "flesh";

    LOG(verbose) << "organ: " << toString();
}

std::string Organ::toString()
{
    std::stringstream ret;
    ret << "[";
    for(auto &b : buffs)
        ret << b << " ";
    ret << "] ";
    ret << string_format("health = %d; material = \"%s\"", health, material.c_str());
    return ret.str();
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
