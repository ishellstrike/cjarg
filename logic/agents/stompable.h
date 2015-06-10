#ifndef STOMPABLE_H
#define STOMPABLE_H
#include "agent.h"

//!
//! \brief Behavior agent
//!
struct Stompable : public Agent
{
    AGENT(Stompable)

    std::string afterstomp;

    Agent *instantiate() const override;
    void deserialize(rapidjson::Value &val) override;

    void Update(const GameTimer &gt, const glm::vec3 &pos, Level &l, const AgentOwner &owner) override;
    void Init(const glm::vec3 &pos, const Level &l) override;
    std::string fullInfo() override {return "";}
    std::string debugInfo() override {return "";}
};


#endif // STOMPABLE_H
