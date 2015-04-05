#include "logic/entity/creature.h"
#include "../agents/wander.h"

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
    if(parts && parts->hasAgent<Wander>()) {
        if(glm::distance(pos, wantedPos) < 0.1)
        {
            wantedPos = {rand()%200 - 100 + pos.x, rand()%200 - 100 + pos.y, pos.z};
        }
    }

    if(wish_list.wishes.size() > 0)
    {
        Wish &w = *wish_list.wishes.begin();
        if(glm::distance(pos, w.linked->pos) > 0.1) {
            auto dir = w.linked->pos - pos;
            dir = glm::normalize(dir);
            pos += dir * (float)gt.elapsed * 10.f;
        } else {
            w.linked->markDone();
            wish_list.wishes.erase(wish_list.wishes.begin());
        }
    }


}

Creature *Creature::instantiate()
{
    Creature *c = new Creature;
    if(parts)
        c->parts = std::unique_ptr<Dynamic>(parts->instantiate());
    c->id = id;

    if(subparts)
        c->subparts = std::unique_ptr<CreaturePart>(subparts->instantiate());

    return c;
}

