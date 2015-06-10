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
#include "logic/map/staticblock.h"
#include "colony.h"

class Level
{
public:
    enum NEIGB
    {
        NEIGB_TOP,
        NEIGB_BOTTOM,
        NEIGB_FRONT,
        NEIGB_BACK,
        NEIGB_LEFT,
        NEIGB_RIGHT,
        NEIGB_AFTER_LAST
    };

    static const glm::vec3 neigb_offset[];

    Level(LevelWorker &lw_);
    ~Level();

    void Draw(SpriteBatch &sb, const glm::vec3 &cam);
    void Preload(Point p, int r);

    std::unique_ptr<Block> &block(const Point3 &p) const;
    std::unique_ptr<Block> &block(const glm::vec3 &p) const;
    std::vector<Block *> neighbours(const glm::vec3 &p) const;
    StaticBlock *block_base(const glm::vec3 &p) const;
    StaticBlock *selected_base() const;
    std::unique_ptr<Block> &selected() const;

    void lClick();
    void rClick();

    std::shared_ptr<Sector> sectorContains(const glm::vec3 &p);
    bool change_at(const Point3 &p, const std::string &id);
    bool change_at(const Point3 &p, Jid id);

    unsigned char ground(const glm::vec3 &p);
    Colony colony;
    void OredersUpdate();

    float zoom = 32;

    SectorMap active;
    LevelWorker &lw;
    void Render(std::shared_ptr<Camera> cam);
    void Update(std::shared_ptr<Camera> cam, GameTimer &gt);
    std::shared_ptr<Material> mat;
    std::shared_ptr<BasicJargShader> basic;

    int vertcount, facecount;
    glm::vec3 m_selected;
    bool finded;
    Mesh selection;
    int slice() const;
    void slice(int __slice);

private:
    int m_slice = RZ - 1;
};

#endif // LEVEL_H
