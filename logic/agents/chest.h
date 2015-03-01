#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>
#include "rapidjson/document.h"

struct Chest : public Agent
{
    AGENT(Chest)

    std::vector<Item> items;

    Agent *instantiate() const;
    void deserialize(rapidjson::Value &val);
};

#endif // CHEST_H
