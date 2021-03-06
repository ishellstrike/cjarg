#ifndef SECTOR_H
#define SECTOR_H
#define RX 16
#define RY 16
#define RZ 64
#define RXYZ RX*RY*RZ
#include "block.h"
#include "scheme.h"
#include <glm/glm.hpp>
#include "point.h"
#include "../entity/creature.h"
#include "../entity/item.h"
#include <memory>
#include "sge/material.h"
#include "sge/basicjargshader.h"
#include "sge/geometry/mesh.h"
#include "sge/camera.h"
#include <list>

#define FORijk for(int i=0; i<RX; ++i) for(int j=0; j<RY; ++j) for (int k=0; k<RZ; ++k)
#define FORij for(int i=0; i<RX; ++i) for(int j=0; j<RY; ++j)

struct Sector
{
    enum {
        READY,
        BUILDING,
        BUILDED,
        EMPTY,
        UNBINDED
    };

    Sector();
    Sector(const Point &p);
    ~Sector();
    Jid blockId(const Point3 &p);
    void Init();

    Block *block(const Point3 &p);
    void block(const Point3 &p, std::shared_ptr<Block> nv);
    void placeScheme(const Scheme &s, glm::vec3 pos);

    void Rebuild(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_, int slice);
    void Rebuild(int slice);
    void MakeSprites(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_, int slice, std::shared_ptr<Camera> cam);

    std::vector<std::vector<std::vector<std::shared_ptr<Block>>>> blocks;
    Point offset;
    typedef std::list<std::shared_ptr<Creature>> CreatureList;
    CreatureList creatures;
    std::vector<Item*> items;

    Mesh mesh;
    Mesh sprites;
    int state = EMPTY;
    int facecount = 0, vertcount = 0;
    bool is_outoffrustum = false;
    bool rebuilding = false;
    bool rebuild_later = false;

    void markRebuild();

    void* operator new(size_t i)
    {
        return _mm_malloc(i, 16);
    }

    void operator delete(void* p)
    {
        _mm_free(p);
    }

private:

    friend struct Generator;
    friend class Level;
};

#endif // SECTOR_H
