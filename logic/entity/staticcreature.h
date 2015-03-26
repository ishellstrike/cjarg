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
};

#endif // STATICCREATURE_H
