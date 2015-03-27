#ifndef FATAL_H
#define FATAL_H
#include "agent.h"
#include "rapidjson/document.h"

//!
//! \brief Item part agent
//!
struct Organ : public Agent
{
    AGENT(Organ)

    std::vector<std::string> buffs;
    int health;
    std::string material;

    void deserialize(rapidjson::Value &val);
    Agent *instantiate() const;
    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
    std::string toString();
};

#endif // FATAL_H
