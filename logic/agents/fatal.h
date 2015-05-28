#ifndef FATAL_H
#define FATAL_H
#include "agent.h"
#include "rapidjson/document.h"
#include <sstream>
#include "gamepart.h"

//!
//! \brief Item part agent
//!
struct Organ : public Agent
{
    AGENT(Organ)

    std::vector<std::string> buffs;
    int health = 1;
    std::string material = "flesh";

    void deserialize(rapidjson::Value &val);
    Agent *instantiate() const;
    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l, const AgentOwner &owner);
    void Init(const glm::vec3 &pos, const Level &l);

    std::string fullInfo()
    {
        return "это орган";
    }

    std::string debugInfo()
    {
        std::stringstream ss;
        ss << "organ ";
        ss << DEBUGINFO(health) << DEBUGINFO(material); return ss.str();
    }
};

#endif // FATAL_H
