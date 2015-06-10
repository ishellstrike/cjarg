#ifndef STATICCREATURE_H
#define STATICCREATURE_H
#include "creature.h"
#include <memory>
#include <string>

class StaticCreature
{
public:
    StaticCreature(){}
    ~StaticCreature(){}
    StaticCreature(const StaticCreature&) = delete;
    StaticCreature& operator=(const StaticCreature&) = delete;

    std::unique_ptr<Creature> etalon;
    std::string full_id;
    int id;

    //trivial vars
    std::string name;
    std::string description;

    void deserialize(const rapidjson::Value &val)
    {
        DESERIALIZE(NVP(name), NVP(description));

        if(val.HasMember("creaturepart") || val["creaturepart"].IsArray()) {
            const rapidjson::Value &d = val["creaturepart"];
            etalon->subparts->deserialize(*d.Begin());
        }
    }

    std::string debugInfo()
    {
        std::stringstream s;
        s << DEBUGINFO(name);
        s << DEBUGINFO(description);

        return s.str();
    }    
};

#endif // STATICCREATURE_H
