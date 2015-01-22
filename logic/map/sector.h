#ifndef SECTOR_H
#define SECTOR_H
#define RX 16
#define RY 16
#define RZ 32
#define RXYZ RX*RY*RZ
#include "block.h"
#include <glm/glm.hpp>
#include "point.h"
#define FORijk for(int i=0; i<RX; i++) for(int j=0; j<RY; j++) for (int k=0; k<RZ; k++)

struct Sector
{
    Sector();
    Sector(const Point &p);
    ~Sector();
    Block *blocks[RX][RY][RZ];
    Point offset;
};

#endif // SECTOR_H
