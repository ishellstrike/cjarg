#ifndef JOINABLE_H
#define JOINABLE_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>
#include "rapidjson/document.h"
#include "../map/staticblock.h"
#include "../map/level.h"

struct Joinable : public Agent
{
    AGENT(Joinable)

    int join_id = 0;

    bool has_joines[StaticBlock::SIDE_AFTER_LAST] = {false, false, false, false, false, false};

    Agent *instantiate() const override;
    void deserialize(rapidjson::Value &val) override;

    void Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner) override;
    void Init(const glm::vec3 &pos, const Level &l) override;
    std::string fullInfo() override {return "";}
    std::string debugInfo() override {return "";}
};

#endif // JOINABLE_H
