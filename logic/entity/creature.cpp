#include "logic/entity/creature.h"

Creature::Creature() :
    Dynamic()
{
}

Creature::~Creature()
{

}
const glm::vec3 &Creature::getWantedPos() const
{
    return wantedPos;
}

void Creature::setWantedPos(const glm::vec3 &value)
{
    wantedPos = value;
}

