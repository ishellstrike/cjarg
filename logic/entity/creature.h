#ifndef CREATURE_H
#define CREATURE_H
#include "../agents/gamepart.h"
#include <glm/glm.hpp>
#include "physic.h"
#include "skilllist.h"

class Creature : public Dynamic, public Physic
{
public:
    Creature();
    ~Creature();

    const glm::vec3 &getWantedPos() const;
    void setWantedPos(const glm::vec3 &value);
    void Update(GameTimer &gt, Level &l);

    SkillList skills;

private:
    glm::vec3 wantedPos;
};

#endif // CREATURE_H
