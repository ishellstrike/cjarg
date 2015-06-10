#ifndef CREATURE_H
#define CREATURE_H
#include "../agents/gamepart.h"
#include <glm/glm.hpp>
#include "physic.h"
#include "skilllist.h"
#include "creaturepart.h"
#include "../agents/gamepart.h"
#include "wishlist.h"
#include "memlist.h"

class StaticCreature;

class Creature : public Physic, public GameBase
{
public:
    ~Creature(){}
    Creature(const Creature&) = delete;
    Creature& operator=(const Creature&) = delete;

    const glm::vec3 &getWantedPos() const;
    void setWantedPos(const glm::vec3 &value);
    void Update(GameTimer &gt, Level &l);
    StaticCreature *getStaticCreature();

    Creature *instantiate();

    SkillList skills;
    std::unique_ptr<CreaturePart> subparts = nullptr;

    WishList wish_list;
    MemList mem_list;

    friend class database;
    glm::vec3 wantedPos;


protected:

    Creature(){}
};

#endif // CREATURE_H
