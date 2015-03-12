#ifndef CHEST_H
#define CHEST_H
#include "agent.h"
#include "../entity/item.h"
#include <vector>
#include "rapidjson/document.h"
#include "../map/staticblock.h"
#include "../map/level.h"

struct Joinable : public Agent
{
    AGENT(Joinable)

    int join_id;

    bool has_joines[StaticBlock::SIDE_AFTER_LAST];

    Agent *instantiate() const;
    void deserialize(rapidjson::Value &val);

    void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l);
    void Init(const glm::vec3 &pos, const Level &l);
};

#endif // CHEST_H
