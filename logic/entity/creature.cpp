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

void Creature::Update(GameTimer &gt, Level &l)
{
    if(glm::distance(pos, wantedPos) < 0.1)
    {
        wantedPos = {rand()%200 - 100 + pos.x, rand()%200 - 100 + pos.y, pos.z};
    }
    auto dir = pos - wantedPos;
    dir = glm::normalize(dir);
    pos += dir * (float)gt.elapsed * 10.f;
}

