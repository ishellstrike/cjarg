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
        DESERIALIZE(name);
        DESERIALIZE(description);
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
