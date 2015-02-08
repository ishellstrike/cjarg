#ifndef CREATURE_H
#define CREATURE_H
#include "../agents/gamepart.h"
#include <glm/glm.hpp>

class Creature : public Dynamic
{
public:
    Creature();
    ~Creature();

    glm::vec3 pos;
};

#endif // CREATURE_H
