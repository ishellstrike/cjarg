#include "sector.h"

Sector::Sector()
{
    FORijk
    {
        blocks[i][j][k] = new Block();
    }
    blocks[0][0][0]->id = 12313;
}

Sector::Sector(const Point &p) :
    offset(p)
{
    FORijk
    {
        blocks[i][j][k] = new Block();
    }
}

Sector::~Sector()
{
    FORijk
    {
        delete blocks[i][j][k];
    }
}

