#define GLM_SWIZZLE
#include "level.h"
#include "sge/textureatlas.h"
#include "sge/colorextender.h"
#include "sge/prefecences.h"
#include <future>
#include "logic/map/trivialgenerator.h"
#include "sge/helper.h"
#include "sge/logger.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include "sge/mouse.h"
#include "sge/geometry/cube.h"
#include "logic/base/database.h"

Level::Level(LevelWorker &lw_) :
    lw(lw_)
{
    basic = std::make_shared<BasicJargShader>();
    basic->loadShaderFromSource(GL_VERTEX_SHADER, "data/shaders/normal.glsl");
    basic->loadShaderFromSource(GL_FRAGMENT_SHADER, "data/shaders/normal.glsl");
    basic->Link();
    basic->Afterlink();

    mat = std::make_shared<Material>();
    mat->texture = TextureAtlas::tex;
    mat->normal = TextureAtlas::tex;

    std::shared_ptr<Material> m = std::make_shared<Material>();
    m->texture = std::make_shared<Texture>();
    m->texture->Load(Prefecences::Instance()->getTexturesDir() + "frame.png");
    m->normal = TextureAtlas::tex;

    selection = Mesh(*Cube::getMesh());
    selection.material = m;
    selection.shader = basic;
    selection.Bind();
}

Level::~Level()
{

}

void Level::Render(std::shared_ptr<Camera> cam)
{
    int x = cam->getPosition().x / RX;
    int y = cam->getPosition().y / RY;
    facecount = vertcount = 0;

    for(auto &pair: lw.mem)
    {
        if(pair.second->state == Sector::READY || pair.second->rebuilding)
        {
            if(pair.second->is_outoffrustum) continue;
            pair.second->mesh.Render(cam->getMVP());
            facecount += pair.second->facecount;
            vertcount += pair.second->vertcount;
        }
    }

    for(auto beg = lw.mem.begin(); beg != lw.mem.end(); )
    {
        if(glm::length(glm::vec2(x, y) - glm::vec2(beg->first.x, beg->first.y)) > 7)
        {
            lw.mem.erase(beg);
            break;
        }
        else
        {
            ++beg;
        }
    }
    if(finded)
    {
        selection.Bind();
        //selection.World = glm::scale(glm::mat4(1), glm::vec3(1.01f,1.01f,1.01f));
        selection.World = glm::translate(glm::mat4(1), m_selected + glm::vec3(0.5,0.5,0.5));
        selection.World = glm::scale(selection.World, glm::vec3(1.1f,1.1f,1.1f));
        glDisable(GL_CULL_FACE);
        selection.Render(cam->getMVP());
        glEnable(GL_CULL_FACE);
    }
}

glm::vec3 SubdivideCheck(const glm::vec3 &min, const glm::vec3 &max, const glm::ray &ray)
{
    if(glm::length(min - max) < 2) return min;

    auto halfsize =  (max - min) / 2.f;

    // -- top layer
    // (0,0,0)
    glm::vec3 new_min = min;
    glm::vec3 new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);
    // (1,0,0)
    new_min = min + glm::vec3(halfsize.x, 0, 0);
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);
    // (0,1,0)
    new_min = min + glm::vec3(0, halfsize.y, 0);
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);
    // (1,1,0)
    new_min = min + glm::vec3(halfsize.x, halfsize.y, 0);
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);

    // -- bottom layer
    // (0,0,1)
    new_min = min;
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);
    // (1,0,1)
    new_min = min + glm::vec3(halfsize.x, 0, halfsize.z);
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);
    // (0,1,1)
    new_min = min + glm::vec3(0, halfsize.y, halfsize.z);
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);
    // (1,1,1)
    new_min = min + glm::vec3(halfsize.x, halfsize.y, halfsize.z);
    new_max = new_min + halfsize;
    if(glm::intersect(ray, 0, RX, new_min, new_max))
        return SubdivideCheck(new_min, new_max, ray);

    return glm::vec3(0);
}

/*!
 * \brief 3d версия алгоритме Брезенхема
 * \param p1 начало отрезка
 * \param p2 конец отрезка
 * \param out_points[out] единичные кубы пространства, пересекающиеся с отрезком
 *
 * Трассировка пересечения заданного отрезка с кубами 1х1х1, на которое виртуально делится все пространство
 */
void Bresencham3D(const glm::vec3 &p1, const glm::vec3 &p2, std::vector<glm::vec3> &out_points)
{
    int x  = static_cast<int>(p1.x);
    int y  = static_cast<int>(p1.y);
    int z  = static_cast<int>(p1.z);
    int dx = static_cast<int>(glm::abs(p2.x - x));
    int dy = static_cast<int>(glm::abs(p2.y - y));
    int dz = static_cast<int>(glm::abs(p2.z - z));
    int sx = static_cast<int>(glm::sign(p2.x - x));
    int sy = static_cast<int>(glm::sign(p2.y - y));
    int sz = static_cast<int>(glm::sign(p2.z - z));

    if( (dy >= dx) && (dy >= dz) )
    {
        register int e_yx = (dx - dy) << 1;
        register int e_yz = (dz - dy) << 1;

        e_yx -= (e_yx >> 1);
        e_yz -= (e_yz >> 1);

        for(register int i = 0; i < dy; ++i)
        {
            out_points.push_back(glm::vec3(x, y, z));
            if(e_yx >= 0)
            {
                x += sx;
                e_yx -= (dy << 1);
                out_points.push_back(glm::vec3(x, y, z));
            }

            if(e_yz >= 0)
            {
                z += sz;
                e_yz -= (dy << 1);
                out_points.push_back(glm::vec3(x, y, z));
            }

            y += sy;
            e_yx += (dx << 1);
            e_yz += (dz << 1);
        }
    }
    else if( (dx >= dy) && (dx >= dz) )
    {
        register int e_xy = (dy - dx) << 1;
        register int e_xz = (dz - dx) << 1;

        e_xz -= (e_xz >> 1);
        e_xy -= (e_xy >> 1);

        for(register int i = 0; i < dx; ++i)
        {
            out_points.push_back(glm::vec3(x, y, z));

            if(e_xy>=0)
            {
                y += sy;
                e_xy -= (dx << 1);
                out_points.push_back(glm::vec3(x, y, z));
            }

            if(e_xz>=0)
            {
                z += sz;
                e_xz -= (dx << 1);
                out_points.push_back(glm::vec3(x, y, z));
            }
            x += sx;
            e_xy +=(dy << 1);
            e_xz +=(dz << 1);
        }
    }
    else // (dz>=dy) && (dz>=dx)
    {
        register int e_zx = (dx - dz) << 1;
        register int e_zy = (dy - dz) << 1;

        e_zx -= (e_zx >> 1);
        e_zy -= (e_zy >> 1);

        for(register int i = 0; i < dz; ++i)
        {
            out_points.push_back(glm::vec3(x, y, z));

            if(e_zx>=0)
            {
                x += sx;
                e_zx -= (dz << 1);
                out_points.push_back(glm::vec3(x, y, z));
            }
            if(e_zy>=0)
            {
                y += sy;
                e_zy -= (dz << 1);
                out_points.push_back(glm::vec3(x, y, z));
            }

            z += sz;
            e_zx += (dx << 1);
            e_zy += (dy << 1);
        }


    }
    out_points.push_back(glm::vec3(x, y, z));
}



void Level::Update(std::shared_ptr<Camera> cam, GameTimer &gt)
{
    glm::vec3 near = glm::unProject(glm::vec3(Mouse::getCursorPos().x, RESY-Mouse::getCursorPos().y, 0.f),  cam->getModel() * cam->getView(), cam->getProjection(),
                                    cam->getViewport());
    glm::vec3 far = glm::unProject(glm::vec3(Mouse::getCursorPos().x, RESY-Mouse::getCursorPos().y, 1.f),  cam->getModel() * cam->getView(), cam->getProjection(),
                                    cam->getViewport());
    glm::ray ray(near, far - near);

    finded = false;
    for(auto &s: lw.mem)
    {
        glm::vec3 pos = glm::vec3(s.second->offset.x*RX, s.second->offset.y*RY, 0);
        s.second->is_outoffrustum = !cam->BoxWithinFrustum(pos, pos + glm::vec3(RX,RY,RZ));
    }

    std::vector<glm::vec3> points;
    auto farpos = ray.origin + ray.dir * (float) RX * 10.f;
    Bresencham3D(ray.origin + glm::vec3(-1, 0.5f, 0), farpos + glm::vec3(-1, 0.5f, 0), points);

    for(glm::vec3 &point : points)
    {
        if(point.z >= RZ - 1 || point.z < 0) continue;
        if(block(point) && block(point)->id() != 0)
        {
            finded = true;
            m_selected = point;
            break;
        }
    }

    for(auto &pair: lw.mem)
    {
        Sector *cur = pair.second.get();
        if(cur->state == Sector::READY || cur->rebuilding)
        {
            for(auto c_iter = cur->creatures.begin(); c_iter != cur->creatures.end();)
            {
                Creature *c = *c_iter;
                c->velocity += c->acseleration;
                c->velocity.z += -29.8 *gt.elapsed;

                glm::vec3 npos;
                npos = c->pos + glm::vec3(c->velocity.x*2, 0, 0) * (float)gt.elapsed;
                if(npos.z > RZ || (npos.z > 0 && block(npos) && block(npos)->id() == 0))
                    c->pos.x = npos.x;
                else
                    c->velocity.x = 0;

                npos = c->pos + glm::vec3(0, c->velocity.y*2, 0) * (float)gt.elapsed;
                if(npos.z > RZ || (npos.z > 0 && block(npos) && block(npos)->id() == 0))
                    c->pos.y = npos.y;
                else
                    c->velocity.y = 0;

                npos = c->pos + glm::vec3(0, 0, c->velocity.z*2) * (float)gt.elapsed;
                if(npos.z > RZ || (npos.z > 0 && block(npos) && block(npos)->id() == 0))
                    c->pos.z = npos.z;
                else
                    c->velocity.z = 0;

                c->velocity.x /= 1.2;
                c->velocity.y /= 1.2;

                if(c->pos.z < 0)
                    c->pos.z = 0;

                // если находится за границей сектора -- переносим в новый сектор, если он существует
                if(c->pos.x > (cur->offset.x + 1)*RX)
                {
                    Sector* nsec = lw.getSector({cur->offset.x + 1, cur->offset.y}, mat, basic);
                    if(nsec)
                    {
                        cur->creatures.erase(c_iter);
                        nsec->creatures.push_back(c);
                        break;
                    }
                }
                if(c->pos.x < (cur->offset.x)*RX)
                {
                    Sector* nsec = lw.getSector({cur->offset.x - 1, cur->offset.y}, mat, basic);
                    if(nsec)
                    {
                        cur->creatures.erase(c_iter);
                        nsec->creatures.push_back(c);
                        break;
                    }
                }
                if(c->pos.y > (cur->offset.y + 1)*RY)
                {
                    Sector* nsec = lw.getSector({cur->offset.x, cur->offset.y + 1}, mat, basic);
                    if(nsec)
                    {
                        cur->creatures.erase(c_iter);
                        nsec->creatures.push_back(c);
                        break;
                    }
                }
                if(c->pos.y < (cur->offset.y)*RY)
                {
                    Sector* nsec = lw.getSector({cur->offset.x, cur->offset.y - 1}, mat, basic);
                    if(nsec)
                    {
                        cur->creatures.erase(c_iter);
                        nsec->creatures.push_back(c);
                        break;
                    }
                }

                //передвигаем итератор, если существо не перемещено
                ++c_iter;
            }
        }
    }
}

void Level::Preload(Point p, int r)
{
    for(int i=-r;i<r;++i)
        for(int j=-r;j<r;++j)
        {
            if(glm::length(glm::vec2((float)i,(float)j) - glm::vec2(0.f, 0.f)) > r) continue;
            Sector *s = lw.getSector({i + p.x, j + p.y}, mat, basic);
            //if(!s) continue;
            //active[Point(i + p.x, j + p.y)] = s;
        }
}

Block *Level::block(const Point3 &p)
{
    int divx = static_cast<int>(p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX);
    int divy = static_cast<int>(p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY);
    if(lw.mem.find({divx, divy}) == lw.mem.end())
        return nullptr;
    auto &sect = lw.mem[Point(divx, divy)];
    return sect->block({p.x - divx * RX, p.y - divy * RY, p.z});
}

Block *Level::block(const glm::vec3 &p)
{
    int divx = static_cast<int>(p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX);
    int divy = static_cast<int>(p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY);
    if(lw.mem.find(Point(divx, divy)) == lw.mem.end())
        return nullptr;
    auto &sect = lw.mem[Point(divx, divy)];
    return sect->block({(int)p.x - divx * RX, (int)p.y - divy * RY, (int)p.z});
}

StaticBlock *Level::block_base(const glm::vec3 &p)
{
    return database::instance()->block_db[block(p)->id()].get();
}

Block *Level::selected()
{
    return block(m_selected);
}

StaticBlock *Level::selected_base()
{
    return database::instance()->block_db[selected()->id()].get();
}

void Level::lClick()
{
    Block *a = selected();
    StaticBlock *b = database::instance()->block_db[a->id()].get();
    b->lClick(a);
}

void Level::rClick()
{
    Block *a = selected();
    StaticBlock *b = database::instance()->block_db[a->id()].get();
    b->rClick(a);
}

std::shared_ptr<Sector> Level::sectorContains(const glm::vec3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(lw.mem.find(Point(divx, divy)) == lw.mem.end())
        return nullptr;
    return lw.mem[Point(divx, divy)];
}

bool Level::change_at(const Point3 &p, const std::string &id)
{
    return change_at(p, database::instance()->block_pointer[id]);
}

bool Level::change_at(const Point3 &p, Jid id)
{
    if(block(p)) {
        int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
        int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
        if(lw.mem.find({divx, divy}) == lw.mem.end())
            return false;
        auto sect = lw.mem[Point(divx, divy)];
        if(sect->state != Sector::READY)
            return false;
        sect->block({p.x - divx * RX, p.y - divy * RY, p.z})->id(id);
        if(!sect->rebuilding)
        {
            sect->rebuilding = true;
            sect->state = Sector::EMPTY;
        } else {
            sect->rebuild_later = true;
        }

        return true;
    }
    return false;
}

unsigned char Level::ground(const glm::vec3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(lw.mem.find(Point(divx, divy)) == lw.mem.end())
        return RZ;
    auto &sect = lw.mem[Point(divx, divy)];
    return 0;
}
