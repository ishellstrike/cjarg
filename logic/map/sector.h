#ifndef SECTOR_H
#define SECTOR_H
#define RX 32
#define RY 32
#define RZ 16
#define RXYZ RX*RY*RZ
#include "block.h"
#include <glm/glm.hpp>
#include "point.h"
#include "../entity/creature.h"
#include "../entity/item.h"
#include <memory>
#include "sge/material.h"
#include "sge/basicjargshader.h"
#include "sge/geometry/mesh.h"
#define FORijk for(int i=0; i<RX; ++i) for(int j=0; j<RY; ++j) for (int k=0; k<RZ; ++k)
#define FORij for(int i=0; i<RX; ++i) for(int j=0; j<RY; ++j)

struct Sector
{
    enum {
        READY,
        BUILDING,
        EMPTY,
        UNBINDED
    };

    Sector();
    Sector(const Point &p);
    ~Sector();
    void blockId(const Point3 &p, Jid i);
    Jid blockId(const Point3 &p);
    void Init();

    Block *block(const Point3 &p);

    void Rebuild(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_);
    void Rebuild();

    Block *blocks[RX][RY][RZ];
    Point offset;
    typedef std::vector<Creature*> CreatureList;
    CreatureList creatures;
    std::vector<Item*> items;

    Mesh mesh;
    int state = EMPTY;
    int facecount = 0, vertcount = 0;
    bool is_outoffrustum = false;
    bool rebuilding = false;
    bool rebuild_later = false;
private:

    friend struct Generator;
    friend class Level;
};

#endif // SECTOR_H
