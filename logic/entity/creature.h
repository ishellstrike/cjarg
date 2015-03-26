#ifndef CREATURE_H
#define CREATURE_H
#include "../agents/gamepart.h"
#include <glm/glm.hpp>
#include "physic.h"
#include "skilllist.h"
#include "creaturepart.h"
#include "../agents/gamepart.h"

class Creature : public Physic
{
public:
    Creature(){}
    ~Creature(){}
    Creature(const Creature&) = delete;
    Creature& operator=(const Creature&) = delete;

    const glm::vec3 &getWantedPos() const;
    void setWantedPos(const glm::vec3 &value);
    void Update(GameTimer &gt, Level &l);
    Creature *instantiate();

    SkillList skills;
    CreaturePart subparts;
    std::unique_ptr<Dynamic> parts = nullptr;
    std::string id = "error";

private:
    glm::vec3 wantedPos;
};

#endif // CREATURE_H
