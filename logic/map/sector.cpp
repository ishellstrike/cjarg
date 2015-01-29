#include "sector.h"

Sector::Sector()
{
    FORijk
    {
        blocks[i][j][k] = new Block();
    }
    blocks[0][0][0]->id(12313);
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

void Sector::blockId(const Point3 &p, Jid i)
{
    blocks[p.x][p.y][p.z]->id(i);
}

Jid Sector::blockId(const Point3 &p)
{
    return blocks[p.x][p.y][p.z]->id();
}

Block *Sector::block(const Point3 &p)
{
    return blocks[p.x][p.y][p.z];
}

