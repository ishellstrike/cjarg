#include "physic.h"


void Physic::Push(const glm::vec3 &dir, float strength)
{
    velocity += glm::normalize(dir) * strength;
}

void Physic::Push(const glm::vec3 &force)
{
    velocity += force;
}
