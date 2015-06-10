#include "logic/entity/creature.h"
#include "../agents/wander.h"
#include "logic/base/database.h"

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
//    if(parts && parts->hasAgent<Wander>()) {
//        if(glm::distance(pos, wantedPos) < 0.1)
//        {
//            wantedPos = {rand()%200 - 100 + pos.x, rand()%200 - 100 + pos.y, pos.z};
//        }
//    }

    if(parts)
        parts->Update(gt, pos, l, ao_this);

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

    ao_this.n = AgentOwner::CREATURE;

    if(parts)
        c->parts = std::unique_ptr<Dynamic>(parts->instantiate());
    c->m_id = m_id;

    if(subparts)
        c->subparts = std::unique_ptr<CreaturePart>(subparts->instantiate());

    return c;
}

StaticCreature *Creature::getStaticCreature()
{
    return database::instance()->getStaticCreature(database::instance()->creature_back_pointer[m_id]);
}

