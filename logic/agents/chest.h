#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>
#include "rapidjson/document.h"

struct Chest : public Agent
{
    AGENT(Chest)

    std::vector<std::unique_ptr<Item>> items;

    Agent *instantiate() const;
    void deserialize(rapidjson::Value &val);

    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
};

#endif // CHEST_H
