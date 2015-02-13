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
#include "sge/cube.h"

Level::Level(LevelWorker &lw_) :
    lw(lw_)
{
    basic = std::make_shared<BasicJargShader>();
    basic->loadShaderFromSource(GL_VERTEX_SHADER, "data/shaders/normal.glsl");
    basic->loadShaderFromSource(GL_FRAGMENT_SHADER, "data/shaders/normal.glsl");
    basic->Link();
    basic->Use();
    basic->Afterlink();

    mat = std::make_shared<Material>();
    mat->texture = TextureAtlas::tex;
    mat->normal = TextureAtlas::tex;

    selection = Cube::getMesh();
    selection.material = mat;
    selection.shader = basic;
    selection.Bind();
}

Level::~Level()
{

}

void Level::Render(std::shared_ptr<Camera> cam)
{
    int x = cam->position.x / RX;
    int y = cam->position.y / RY;
    facecount = vertcount = 0;

    for(auto &pair: lw.mem)
    {
        if(pair.second->state == Sector::READY)
        {
            if(pair.second->is_outoffrustum) continue;
            pair.second->mesh.Render(cam->MVP);
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
        selection.World = glm::scale(glm::mat4(1), glm::vec3(1,1,1));
        selection.World = glm::translate(selection.World, selected);
        selection.World = glm::scale(selection.World, glm::vec3(32,32,32));
        selection.Render(cam->projection);
    }
}

void Level::Update(std::shared_ptr<Camera> cam)
{
    glm::vec3 near = glm::unProject(glm::vec3(Mouse::GetCursorPos(), 0.f), cam->model * cam->view, cam->projection,
                                    cam->viewport);
    glm::vec3 far = glm::unProject(glm::vec3(Mouse::GetCursorPos(), 1.f), cam->model * cam->view, cam->projection,
                                    cam->viewport);
    glm::ray ray(near, far - near);

    finded = false;
    float len = INT_MAX;
    for(auto &s: lw.mem)
    {
        glm::vec3 pos = glm::vec3(s.second->offset.x*RX, s.second->offset.y*RY, 0);
        s.second->is_outoffrustum = !cam->BoxWithinFrustum(pos, pos + glm::vec3(RX,RY,RZ));
        if(!s.second->is_outoffrustum)
        {
            bool inter = glm::intersect(ray, 0, 100000, pos, pos + glm::vec3(RX,RY,RZ));
            if(inter) {
                finded = true;
                float t_len = glm::length(pos - cam->position);
                if(t_len < len)
                {
                    len = t_len;
                    selected = pos;
                }
            }
        }
    }

//    if(inter) {
//        FORijk
//        {
//            glm::vec3 pos2 = pos + glm::vec3(i,j,k);
//            bool inter2 = glm::intersect(ray, 0, 100000, pos, pos + glm::vec3(1,1,1));
//            if(inter2) {
//            finded = true;
//            selected = pos;
//            LOG(info) << std::to_string(pos);
//            }
//        }
//    }
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
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(active.find({divx, divy}) == active.end())
        return nullptr;
    auto &sect = active[Point(divx, divy)];
    return sect->block({p.x - divx * RX, p.y - divy * RY, p.z});
}

Block *Level::block(const glm::vec3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(active.find({divx, divy}) == active.end())
        return nullptr;
    auto &sect = active[Point(divx, divy)];
    return sect->block({(int)p.x - divx * RX, (int)p.y - divy * RY, (int)p.z});
}

unsigned char Level::ground(const glm::vec3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(active.find({divx, divy}) == active.end())
        return RZ;
    auto &sect = active[Point(divx, divy)];
    return 0;
}

