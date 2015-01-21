#include "sector.h"

Sector::Sector()
{
    FOR
    {
        blocks[i][j][k] = new Block();
    }
}

Sector::Sector(const Point &p) :
    offset(p)
{
    FOR
    {
        blocks[i][j][k] = new Block();
    }
}

Sector::~Sector()
{
    FOR
    {
        delete blocks[i][j][k];
    }
}

