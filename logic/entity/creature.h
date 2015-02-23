#ifndef CREATURE_H
#define CREATURE_H
#include "../agents/gamepart.h"
#include <glm/glm.hpp>
#include "physic.h"

class Creature : public Dynamic, public Physic
{
public:
    Creature();
    ~Creature();

};

#endif // CREATURE_H
