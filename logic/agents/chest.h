#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>
#include "rapidjson/document.h"

//!
//! \brief universal item store agents; 100% items drops on death
//!
struct Chest : public Agent
{
    AGENT(Chest)

    std::vector<std::unique_ptr<Item>> items;

    Agent *instantiate() const;
    void deserialize(rapidjson::Value &val);

    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
    std::string fullInfo(){return "";}
    std::string debugInfo(){return "";}
};

#endif // CHEST_H
