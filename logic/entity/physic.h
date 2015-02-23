#ifndef PHYSIC_H
#define PHYSIC_H
#include "glm/glm.hpp"

class Physic
{
public:
    glm::vec3 pos = glm::vec3(0);
    glm::vec3 acseleration = glm::vec3(0);
    glm::vec3 velocity = glm::vec3(0);
};

#endif // PHYSIC_H
