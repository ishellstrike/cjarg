#ifndef LEVEL_H
#define LEVEL_H
#include <unordered_map>
#include <glm/glm.hpp>
#include "sector.h"
#include "sectormap.h"
#include "sge/spritebatch.h"
#include "levelworker.h"
#include "sge/material.h"
#include "sge/basicjargshader.h"
#include "sge/camera.h"

class Level
{
public:
    Level(LevelWorker &lw_);
    ~Level();

    void Draw(SpriteBatch &sb, const glm::vec3 &cam);
    void Preload(Point p, int r);

    Block *block(const Point3 &p);
    Block *block(const glm::vec3 &p);
    std::shared_ptr<Sector> sectorContains(const glm::vec3 &p);
    bool change_at(const Point3 &p, const std::string &id);
    bool change_at(const Point3 &p, Jid id);

    unsigned char ground(const glm::vec3 &p);

    float zoom = 32;

    SectorMap active;
    LevelWorker &lw;
    void Render(std::shared_ptr<Camera> cam);
    void Update(std::shared_ptr<Camera> cam, GameTimer &gt);
    std::shared_ptr<Material> mat;
    std::shared_ptr<BasicJargShader> basic;

    int vertcount, facecount;
    glm::vec3 selected;
    bool finded;
    Mesh selection;
};

#endif // LEVEL_H
