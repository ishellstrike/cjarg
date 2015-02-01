#define GLM_SWIZZLE
#include "level.h"
#include "sge/textureatlas.h"
#include "sge/colorextender.h"
#include "jhelper.inl"
#include "settings.h"

Level::Level(LevelWorker &lw_) :
    lw(lw_)
{
}

Level::~Level()
{

}

void Level::Draw(SpriteBatch &sb, const glm::vec3 &cam_)
{
    auto cam = cam_*glm::vec3(zoom,zoom,1) - glm::vec3(RESX/2.f, RESY/2.f, 0.f);
    //cam.z /= (float)RZ;
    for(SectorMapPair pair: active)
    {
        Point off = pair.second->offset;
        Point secpos = {off.x*zoom*RX, off.y*zoom*RY};
        if(inLimsV(glm::vec2(secpos.x, secpos.y),
                   glm::vec2(cam.x - zoom*RX,       cam.y - zoom*RY),
                   glm::vec2(cam.x + RESX,        cam.y + RESY)))
        {
            FORij
            {
                int top = pair.second->ground[i][j];
                int id = pair.second->blockId({i, j, top});
                Jid jid = id;
                if(cam.z <= top)
                {
                    jid = 5;
                }
                int cur = glm::min(cam.z, (float)top);
                if(id)
                    sb.drawQuadAtlas({i*zoom + secpos.x - cam.x, j*zoom + secpos.y - cam.y},
                                     {zoom, zoom}, TextureAtlas::tex, jid, Color::White * (1 - glm::abs(cur - cam.z)/(float)RZ));
            }

            for(Creature* c: pair.second->creatures)
            {
                sb.drawQuadAtlas(c->pos.xy() * zoom - cam.xy(), {zoom ,zoom}, TextureAtlas::tex, 22, Color::White);
            }
        }
    }
}

void Level::Preload(Point p, int r)
{
    for(int i=0;i<r;i++)
        for(int j=0;j<r;j++)
        {
            active[Point(i, j)] = lw.getSector({i, j});
        }
}

Block *Level::block(const Point3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(active.find({divx, divy}) == active.end())
        return nullptr;
    Sector *sect = active[Point(divx, divy)];
    return sect->block({p.x - divx * RX, p.y - divy * RY, p.z});
}

Block *Level::block(const glm::vec3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(active.find({divx, divy}) == active.end())
        return nullptr;
    Sector *sect = active[Point(divx, divy)];
    return sect->block({(int)p.x - divx * RX, (int)p.y - divy * RY, (int)p.z});
}

unsigned char Level::ground(const glm::vec3 &p)
{
    int divx = p.x < 0 ? (p.x + 1) / RX - 1 : p.x / RX;
    int divy = p.y < 0 ? (p.y + 1) / RY - 1 : p.y / RY;
    if(active.find({divx, divy}) == active.end())
        return RZ;
    Sector *sect = active[Point(divx, divy)];
    return sect->ground[(int)p.x - divx * RX][(int)p.y - divy * RY];
}

