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

const glm::vec3 Level::neigb_offset[] = {
    glm::vec3(0, 0,-1), glm::vec3( 0, 0, 1),
    glm::vec3(1, 0, 0), glm::vec3(-1, 0, 0),
    glm::vec3(0, 1, 0), glm::vec3( 0,-1, 0)
};

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

    for(int i =0; i< 10; i++){
        auto c = database::instantiateCreature("human");
        c->pos = {rand()%RX,rand()%RY,2};
        colony.team.push_back(c);
    }
}

Level::~Level()
{

}

void Level::Render(std::shared_ptr<Camera> cam)
{
    int x = cam->getPosition().x / RX;
    int y = cam->getPosition().y / RY;
    facecount = vertcount = 0;

    for(std::pair<const Point, std::shared_ptr<Sector>> &pair: lw.mem)
    {
        if(pair.second->state == Sector::READY || pair.second->rebuilding || pair.second->state == Sector::BUILDED)
        {
            if(pair.second->is_outoffrustum) continue;

            if(pair.second->state == Sector::BUILDED)
            {
                pair.second->Rebuild(mat, basic, m_slice);
            }
            if(pair.second->state == Sector::UNBINDED)
            {
                pair.second->mesh.ForgetBind();
                pair.second->state = Sector::READY;
                if(!pair.second->rebuild_later)
                    pair.second->rebuilding = false;
                else
                    pair.second->state = Sector::EMPTY;
                pair.second->rebuild_later = false;
            }

            pair.second->mesh.Render(cam->getMVP());
            pair.second->MakeSprites(mat, basic, m_slice, cam);
            glDisable(GL_CULL_FACE);
            pair.second->sprites.Bind(1);
            pair.second->sprites.Render(cam->getMVP());
            glEnable(GL_CULL_FACE);


            facecount += pair.second->facecount;
            vertcount += pair.second->vertcount;
        }
    }

    decltype(lw.mem.begin()) last_ok;
    for(auto beg = lw.mem.begin(); beg != lw.mem.end(); )
    {
        if(glm::length(glm::vec2(x, y) - glm::vec2(beg->first.x, beg->first.y)) > 7)
        {
            lw.mem.erase(beg);
            beg = last_ok;
            break;
        }
        else
        {
            last_ok = beg;
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
                std::shared_ptr<Creature> c = *c_iter;

                c->Update(gt, *this);

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

                c->velocity.x /= 1.2f;
                c->velocity.y /= 1.2f;

                if(c->pos.z < 0)
                    c->pos.z = 0;

                ++c_iter;
            }

            for(auto c_iter = cur->creatures.begin(); c_iter != cur->creatures.end();)
            {
                std::shared_ptr<Creature> c = *c_iter;

                // если находится за границей сектора -- переносим в новый сектор, если он существует
                if(c->pos.x > (cur->offset.x + 1) * RX ||
                   c->pos.x < (cur->offset.x    ) * RX ||
                   c->pos.y > (cur->offset.y + 1) * RY ||
                   c->pos.y < (cur->offset.y    ) * RY )
                {
                    int sx = c->pos.x / RX;
                    int sy = c->pos.y / RY;
                    Sector *nsec = lw.getSector({sx, sy}, mat, basic, m_slice);
                    if(nsec)
                    {
                        cur->creatures.erase(c_iter);
                        nsec->creatures.push_back(std::move(c));
                        break;
                    }
                }
                //передвигаем итератор, если существо не перемещено
                ++c_iter;
            }
        }
    }
    OredersUpdate();
}
int Level::slice() const
{
    return m_slice;
}

void Level::slice(int __slice)
{
    m_slice = __slice;
    m_slice = glm::max(m_slice, 1);
    m_slice = glm::min(m_slice, RZ - 1);

    for(auto s : lw.mem)
    {
        s.second->markRebuild();
    }
}


void Level::Preload(Point p, int r)
{
    for(int i=-r;i<r;++i)
        for(int j=-r;j<r;++j)
        {
            if(glm::length(glm::vec2((float)i,(float)j) - glm::vec2(0.f, 0.f)) > r) continue;
            Sector *s = lw.getSector({i + p.x, j + p.y}, mat, basic, m_slice);
            //if(!s) continue;
            //active[Point(i + p.x, j + p.y)] = s;
        }
}

Block *Level::block(const Point3 &p) const
{
    int divx = static_cast<int>(p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX);
    int divy = static_cast<int>(p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY);
    if(lw.mem.find({divx, divy}) == lw.mem.end())
        return nullptr;
    auto &sect = lw.mem[Point(divx, divy)];
    return sect->block({p.x - divx * RX, p.y - divy * RY, p.z});
}

Block *Level::block(const glm::vec3 &p) const
{
    int divx = static_cast<int>(p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX);
    int divy = static_cast<int>(p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY);
    if(lw.mem.find(Point(divx, divy)) == lw.mem.end())
        return nullptr;
    auto &sect = lw.mem[Point(divx, divy)];
    return sect->block({(int)p.x - divx * RX, (int)p.y - divy * RY, (int)p.z});
}

std::vector<Block *> Level::neighbours(const glm::vec3 &p) const
{
    std::vector<Block *> result;
    for(auto &offset : neigb_offset)
        result.push_back(block(p + offset));
    return result;
}

StaticBlock *Level::block_base(const glm::vec3 &p) const
{
    return database::instance()->block_db[block(p)->id()].get();
}

Block *Level::selected() const
{
    return block(m_selected);
}

StaticBlock *Level::selected_base() const
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

        sect->markRebuild();

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

void Level::OredersUpdate()
{
    for(OrderList::Olist::iterator i = colony.orders.active.begin(); i!=colony.orders.active.end(); ++i)
    {
        std::shared_ptr<Order> o = *i;
        for(std::shared_ptr<Creature> c : colony.team)
        {
            if(c->wish_list.wishCount() != 0) continue;
            Wish w;
            w.linked = o;
            c->wish_list.addWish(w);
            c->mem_list.addMem({"получил приказ"});
            c->wantedPos = o->pos;
            colony.orders.in_progress.push_back(o);
            colony.orders.active.erase(i);
            goto out_p;
        }
    }
    out_p:
    ;

    for(OrderList::Olist::iterator i = colony.orders.in_progress.begin(); i!=colony.orders.in_progress.end(); ++i)
    {
        std::shared_ptr<Order> o = *i;
        if(o->type == Order::Done){
            colony.orders.in_progress.erase(i);
            break;
        }
    }
}
