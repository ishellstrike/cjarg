#include "sector.h"

Sector::Sector()
{
    Block *start = &blocks[0][0][0];
    for(int i = 0; i < RXYZ; i++, start++)
        start = new Block();
}

Sector::Sector(const Point &p) :
    offset(p)
{

}

Sector::~Sector()
{

}

