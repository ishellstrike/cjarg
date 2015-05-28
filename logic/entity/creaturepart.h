#ifndef CREATUREPART_H
#define CREATUREPART_H
#include <string>
#include <vector>
#include <memory>
#include "../agents/agent.h"
#include "rapidjson/document.h"

struct CreaturePart
{
    std::string id  = "";
    int count = 0;
    std::vector<std::unique_ptr<CreaturePart>> subparts;
    void deserialize(const rapidjson::Value &val, int depth = 0);
    CreaturePart *instantiate() const;

    CreaturePart(){}
    ~CreaturePart(){}
    CreaturePart(const CreaturePart&) = delete;
    CreaturePart& operator=(const CreaturePart&) = delete;
};

#endif // CREATUREPART_H
