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

    Agent *instantiate() const override;
    void deserialize(rapidjson::Value &val) override;

    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l, const AgentOwner &owner) override;
    void Init(const glm::vec3 &pos, const Level &l) override;
    std::string fullInfo() override {return "";}
    std::string debugInfo() override {return "";}
};

#endif // CHEST_H
