#ifndef SECTOR_H
#define SECTOR_H
#define RX 16
#define RY 16
#define RZ 32
#define RXYZ RX*RY*RZ
#include "block.h"
#include <glm/glm.hpp>

struct Sector
{
    Sector();
    ~Sector();
    Block blocks[RX][RY][RZ];
    glm::vec2 offset;
};

#endif // SECTOR_H
