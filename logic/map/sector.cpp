#include "sector.h"

Sector::Sector()
{
    Block *start = &blocks[0][0][0];
    for(int i = 0; i < RXYZ; i++, start++)
        start = new Block();
}

Sector::~Sector()
{

}

