#include "sector.h"
#include "glm/gtx/transform.hpp"
#include "sge/textureatlas.h"
#include <mutex>
#include "sge/logger.h"
#include <thread>
#include <chrono>
#include "logic/base/database.h"
#include "sge/helper.h"
#include "sge/geometry/quad.h"

Sector::Sector() :
    mesh(),
    creatures(),
    items(),
    blocks()
{
    Init();
}

Sector::Sector(const Point &p) :
    offset(p),
    mesh(),
    creatures(),
    items(),
    blocks()
{
    Init();
}

Sector::~Sector()
{
    FORijk
    {
        delete blocks[i][j][k];
    }
    blocks.clear();
}

void Sector::blockId(const Point3 &p, Jid i)
{
    blocks[p.x][p.y][p.z]->id(i);
}

Jid Sector::blockId(const Point3 &p)
{
    return blocks[p.x][p.y][p.z]->id();
}

void Sector::Init()
{
    blocks.resize(RX);
    for(int i = 0; i < RX; i++)
    {
        blocks[i].resize(RY);
        for(int j = 0; j < RY; j++)
        {
            blocks[i][j].resize(RZ);
            for(int k = 0; k < RZ; k++)
                blocks[i][j][k] = new Block();
        }
    }

    for(int i = 0; i<rand()%30; i++)
    {
        std::shared_ptr<Creature> c = std::make_shared<Creature>();
        c->pos = {rand()%RX, rand()%RY, rand()%RZ};
        creatures.push_back(c);
    }
}

Block *Sector::block(const Point3 &p)
{
    return blocks[p.x][p.y][p.z];
}

void Sector::block(const Point3 &p, Jid i)
{
    blocks[p.x][p.y][p.z]->id(i);
}

void Sector::block(const Point3 &p, std::string s)
{
    auto db = database::instance();
    blocks[p.x][p.y][p.z]->id(db->block_db[db->block_pointer[s]]->id);
}

void Sector::placeScheme(const Scheme &s, glm::vec3 pos)
{
    for(int i = 0; i < s.size.x && pos.x + i < RX; i++)
    {
        for(int j = 0; j < s.size.y && pos.y + j < RY; j++)
        {
            Letter l = s.data[j][i];
            if(l == '.') continue;
            auto dict = s.dict.find(l);
            std::string st = dict->second;
            block({pos.x + i, pos.y + j, pos.z}, st);
        }
    }
}

void Sector::Rebuild(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_, int slice)
{
    mesh.World = glm::translate(glm::mat4(1), glm::vec3(offset.x * RX, offset.y * RY, 0));
    mesh.material = mat_;
    mesh.shader = basic_;

    mesh.Vertices.reserve(10000);
    mesh.Indices.reserve(10000);

    Rebuild(slice);
}

void Sector::Rebuild(int slice)
{
    mesh.Vertices.clear();
    mesh.Indices.clear();
    register int c = 0;
    FORijk
    {
        // 1 y -
        // 2 x +
        // 3 x -
        // 4 y +
        // 5 z -
        // 6 z +

        if(k >= slice) continue;
        //if(!database::instance()->block_db[blocks[i][j][k]->id()]->cube) continue;

        register Jtex apos = blocks[i][j][k]->id();
        if(!apos) continue;
        float qq,ww,q,w;

        if(j == 0 || database::instance()->block_db[blocks[i][j - 1][k]->id()]->transparent ||
                     !database::instance()->block_db[blocks[i][j - 1][k]->id()]->cube)
        {
            get_uvs(database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_BACK],
                    q,w,qq,ww);

            mesh.Vertices.push_back(VertPosNormTanBiTex({0,1,0}, {i,     j,     k    }, {q, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,1,0}, {i + 1, j,     k    }, {qq, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,1,0}, {i + 1, j,     k + 1}, {qq, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,1,0}, {i    , j,     k + 1}, {q, w}));

            mesh.Indices.push_back(c + 0);
            mesh.Indices.push_back(c + 1);
            mesh.Indices.push_back(c + 2);

            mesh.Indices.push_back(c + 2);
            mesh.Indices.push_back(c + 3);
            mesh.Indices.push_back(c + 0);
            c+=4;
        }

        if(i == RX - 1 || database::instance()->block_db[blocks[i+1][j][k]->id()]->transparent ||
                          !database::instance()->block_db[blocks[i+1][j][k]->id()]->cube)
        {
            get_uvs(database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_RIGHT],
                    q,w,qq,ww);

            mesh.Vertices.push_back(VertPosNormTanBiTex({-1,0,0}, {i + 1, j,     k + 1}, {q, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({-1,0,0}, {i + 1, j,     k    }, {q, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({-1,0,0}, {i + 1, j + 1, k    }, {qq, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({-1,0,0}, {i + 1, j + 1, k + 1}, {qq, w}));

            mesh.Indices.push_back(c + 0);
            mesh.Indices.push_back(c + 1);
            mesh.Indices.push_back(c + 2);

            mesh.Indices.push_back(c + 2);
            mesh.Indices.push_back(c + 3);
            mesh.Indices.push_back(c + 0);
            c+=4;
        }

        if(i == 0 || database::instance()->block_db[blocks[i - 1][j][k]->id()]->transparent ||
                     !database::instance()->block_db[blocks[i - 1][j][k]->id()]->cube)
        {
            get_uvs(database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_LEFT],
                    q,w,qq,ww);

            mesh.Vertices.push_back(VertPosNormTanBiTex({1,0,0}, {i    , j,     k    }, {qq, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({1,0,0}, {i    , j,     k + 1}, {qq, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({1,0,0}, {i    , j + 1, k + 1}, {q, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({1,0,0}, {i    , j + 1, k    }, {q, ww}));

            mesh.Indices.push_back(c + 0);
            mesh.Indices.push_back(c + 1);
            mesh.Indices.push_back(c + 2);

            mesh.Indices.push_back(c + 2);
            mesh.Indices.push_back(c + 3);
            mesh.Indices.push_back(c + 0);
            c+=4;
        }

        if(j == RY - 1 || database::instance()->block_db[blocks[i][j+1][k]->id()]->transparent ||
                          !database::instance()->block_db[blocks[i][j+1][k]->id()]->cube)
        {
            get_uvs(database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_FRONT],
                    q,w,qq,ww);

            mesh.Vertices.push_back(VertPosNormTanBiTex({0,-1,0}, {i    , j + 1, k    }, {qq, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,-1,0}, {i    , j + 1, k + 1}, {qq, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,-1,0}, {i + 1, j + 1, k + 1}, {q, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,-1,0}, {i + 1, j + 1, k    }, {q, ww}));

            mesh.Indices.push_back(c + 0);
            mesh.Indices.push_back(c + 1);
            mesh.Indices.push_back(c + 2);

            mesh.Indices.push_back(c + 2);
            mesh.Indices.push_back(c + 3);
            mesh.Indices.push_back(c + 0);
            c+=4;
        }

        if(k == 0 || database::instance()->block_db[blocks[i][j][k - 1]->id()]->transparent ||
                     !database::instance()->block_db[blocks[i][j][k - 1]->id()]->cube)
        if(k != 0)
        {
            get_uvs(database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_BOTTOM],
                    q,w,qq,ww);

            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,1}, {i + 1, j    , k    }, {q, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,1}, {i    , j    , k    }, {qq, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,1}, {i    , j + 1, k    }, {qq, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,1}, {i + 1, j + 1, k    }, {q, ww}));

            mesh.Indices.push_back(c + 0);
            mesh.Indices.push_back(c + 1);
            mesh.Indices.push_back(c + 2);

            mesh.Indices.push_back(c + 2);
            mesh.Indices.push_back(c + 3);
            mesh.Indices.push_back(c + 0);
            c+=4;
        }

        if(k == RZ - 1 || database::instance()->block_db[blocks[i][j][k + 1]->id()]->transparent ||
                          !database::instance()->block_db[blocks[i][j][k + 1]->id()]->cube || k == slice - 1)
        {
            get_uvs(database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_TOP],
                    q,w,qq,ww);

            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i    , j    , k + 1}, {qq, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i + 1, j    , k + 1}, {q, w}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i + 1, j + 1, k + 1}, {q, ww}));
            mesh.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i    , j + 1, k + 1}, {qq, ww}));

            mesh.Indices.push_back(c + 0);
            mesh.Indices.push_back(c + 1);
            mesh.Indices.push_back(c + 2);

            mesh.Indices.push_back(c + 2);
            mesh.Indices.push_back(c + 3);
            mesh.Indices.push_back(c + 0);
            c+=4;
        }
    }

    facecount = mesh.Indices.size() / 3;
    vertcount = mesh.Vertices.size();

    state = UNBINDED;
}

void addBillboard(Mesh &m, glm::vec3 pos, int tex, std::shared_ptr<Camera> cam)
{
    float qq,ww,q,w;
    get_uvs(tex,q,w,qq,ww);

    int i = pos.x;
    int j = pos.y;
    int k = pos.z;

    int c = m.Vertices.size();

    m.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i    , j,     k + 1}, {qq, w}));
    m.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i + 1, j,     k + 1}, {q, w}));
    m.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i + 1, j + 1, k + 1}, {q, ww}));
    m.Vertices.push_back(VertPosNormTanBiTex({0,0,-1}, {i    , j + 1, k + 1}, {qq, ww}));

    m.Indices.push_back(c + 0);
    m.Indices.push_back(c + 1);
    m.Indices.push_back(c + 2);

    m.Indices.push_back(c + 2);
    m.Indices.push_back(c + 3);
    m.Indices.push_back(c + 0);
}

void Sector::MakeSprites(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_, int slice, std::shared_ptr<Camera> cam)
{
    sprites.World = glm::translate(glm::mat4(1), glm::vec3(offset.x * RX, offset.y * RY, 0));
    sprites.material = mat_;
    sprites.shader = basic_;

    sprites.Vertices.reserve(10000);
    sprites.Indices.reserve(10000);

    sprites.Vertices.clear();
    sprites.Indices.clear();

    for(std::shared_ptr<Creature> c : creatures)
    {
        addBillboard(sprites, c->pos, 1, cam);
    }

//    FORijk
//    {
//        if(!database::instance()->block_db[blocks[i][j][k]->id()]->cube)
//            addBillboard(sprites, {i,j,k}, database::instance()->block_db[blocks[i][j][k]->id()]->tex[StaticBlock::SIDE_TOP], cam);
//    }
}

void Sector::markRebuild()
{
    if(!rebuilding)
    {
        rebuilding = true;
        state = Sector::EMPTY;
    } else {
        rebuild_later = true;
    }
}

