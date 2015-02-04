#ifndef SECTOR_H
#define SECTOR_H
#define RX 64
#define RY 64
#define RZ 16
#define RXYZ RX*RY*RZ
#include "block.h"
#include <glm/glm.hpp>
#include "point.h"
#include "../entity/creature.h"
#include "../entity/item.h"
#include "sge/mesh.h"
#include "GL/glew.h"
#include <memory>
#define FORijk for(int i=0; i<RX; i++) for(int j=0; j<RY; j++) for (int k=0; k<RZ; k++)
#define FORij for(int i=0; i<RX; i++) for(int j=0; j<RY; j++)

struct Sector
{
    Sector();
    Sector(const Point &p);
    ~Sector();
    void blockId(const Point3 &p, Jid i);
    Jid blockId(const Point3 &p);

    Block *block(const Point3 &p);

    void Rebuild(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_);

    Block *blocks[RX][RY][RZ];
    unsigned char ground[RX][RY];
    Point offset;
    std::vector<Creature*> creatures;
    std::vector<Item*> items;

    Mesh mesh;
private:

    friend struct Generator;
    friend class Level;
};

#endif // SECTOR_H
