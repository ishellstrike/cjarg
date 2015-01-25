#include "level.h"
#include "textureatlas.h"
#include "colorextender.h"
#include "jhelper.inl"
#include "settings.h"

Level::Level(LevelWorker &lw_) :
    lw(lw_)
{
}

Level::~Level()
{

}

void Level::Draw(SpriteBatch &sb, const glm::vec3 &cam)
{
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
                                     {zoom, zoom}, TextureAtlas::tex, jid, WHITE * (1 - glm::abs(cur - cam.z)/(float)RZ));
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

