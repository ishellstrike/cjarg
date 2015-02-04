#include "sector.h"
#include "glm/gtx/transform.hpp"
#include "sge/textureatlas.h"

Sector::Sector()
{
    FORijk
    {
        blocks[i][j][k] = new Block();
    }
    blocks[0][0][0]->id(12313);
}

Sector::Sector(const Point &p) :
    offset(p)
{
    FORijk
    {
        blocks[i][j][k] = new Block();
    }
}

Sector::~Sector()
{
    FORijk
    {
        delete blocks[i][j][k];
    }
}

void Sector::blockId(const Point3 &p, Jid i)
{
    blocks[p.x][p.y][p.z]->id(i);
}

Jid Sector::blockId(const Point3 &p)
{
    return blocks[p.x][p.y][p.z]->id();
}

Block *Sector::block(const Point3 &p)
{
    return blocks[p.x][p.y][p.z];
}

void Sector::Rebuild(std::shared_ptr<Material> mat_, std::shared_ptr<BasicJargShader> basic_)
{
    mesh.Vertices.clear();
    mesh.Indices.clear();
    mesh.World = glm::translate(glm::mat4(1), glm::vec3(offset.x * RX, offset.y * RY, 0));
    mesh.material = mat_;
    mesh.shader = basic_;

    int c = 0;
    FORijk
    {
        // 1 y -
        // 2 x +
        // 3 x -
        // 4 y +
        // 5 z -
        // 6 z +

        Jtex apos = blocks[i][j][k]->id();
        if(apos) continue;
        apos = TextureAtlas::refs["briwall1.png"];
        float qq = 32 / (float) mesh.material->texture->width;
        float ww = 32 / (float) mesh.material->texture->height;
        int inrow = mesh.material->texture->width / 32;
        float q = (apos % inrow) * qq;
        float w = (apos / inrow) * ww;
        qq += q; ww += w;

        if(j == 0 || blocks[i][j - 1][k]->id() != 0)
        {
        mesh.Vertices.push_back(VPNTBT({i,     j,     k    }, {q, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j,     k    }, {qq, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j,     k + 1}, {qq, ww}));
        mesh.Vertices.push_back(VPNTBT({i    , j,     k + 1}, {q, ww}));

        mesh.Indices.push_back(c + 0);
        mesh.Indices.push_back(c + 1);
        mesh.Indices.push_back(c + 2);

        mesh.Indices.push_back(c + 2);
        mesh.Indices.push_back(c + 3);
        mesh.Indices.push_back(c + 0);
        c+=4;
        }

        if(i == RX - 1 || blocks[i+1][j][k]->id() != 0)
        {
        mesh.Vertices.push_back(VPNTBT({i + 1, j,     k + 1}, {q, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j,     k    }, {qq, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j + 1, k    }, {qq, ww}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j + 1, k + 1}, {q, ww}));

        mesh.Indices.push_back(c + 0);
        mesh.Indices.push_back(c + 1);
        mesh.Indices.push_back(c + 2);

        mesh.Indices.push_back(c + 2);
        mesh.Indices.push_back(c + 3);
        mesh.Indices.push_back(c + 0);
        c+=4;
        }

        if(i == 0 || blocks[i - 1][j][k]->id() != 0)
        {
        mesh.Vertices.push_back(VPNTBT({i    , j,     k    }, {q, w}));
        mesh.Vertices.push_back(VPNTBT({i    , j,     k + 1}, {qq, w}));
        mesh.Vertices.push_back(VPNTBT({i    , j + 1, k + 1}, {qq, ww}));
        mesh.Vertices.push_back(VPNTBT({i    , j + 1, k    }, {q, ww}));

        mesh.Indices.push_back(c + 0);
        mesh.Indices.push_back(c + 1);
        mesh.Indices.push_back(c + 2);

        mesh.Indices.push_back(c + 2);
        mesh.Indices.push_back(c + 3);
        mesh.Indices.push_back(c + 0);
        c+=4;
        }

        if(j == RY - 1 || blocks[i][j+1][k]->id() != 0)
        {
        mesh.Vertices.push_back(VPNTBT({i    , j + 1, k    }, {q, w}));
        mesh.Vertices.push_back(VPNTBT({i    , j + 1, k + 1}, {qq, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j + 1, k + 1}, {qq, ww}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j + 1, k    }, {q, ww}));

        mesh.Indices.push_back(c + 0);
        mesh.Indices.push_back(c + 1);
        mesh.Indices.push_back(c + 2);

        mesh.Indices.push_back(c + 2);
        mesh.Indices.push_back(c + 3);
        mesh.Indices.push_back(c + 0);
        c+=4;
        }

        if(k == 0 || blocks[i][j][k - 1]->id() != 0)
        {
        mesh.Vertices.push_back(VPNTBT({i + 1, j    , k    }, {q, w}));
        mesh.Vertices.push_back(VPNTBT({i    , j    , k    }, {qq, w}));
        mesh.Vertices.push_back(VPNTBT({i    , j + 1, k    }, {qq, ww}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j + 1, k    }, {q, ww}));

        mesh.Indices.push_back(c + 0);
        mesh.Indices.push_back(c + 1);
        mesh.Indices.push_back(c + 2);

        mesh.Indices.push_back(c + 2);
        mesh.Indices.push_back(c + 3);
        mesh.Indices.push_back(c + 0);
        c+=4;
        }

        if(k == RZ - 1 || blocks[i][j][k + 1]->id() != 0)
        if(k != RZ - 1)
        {
        mesh.Vertices.push_back(VPNTBT({i    , j    , k + 1}, {q, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j    , k + 1}, {qq, w}));
        mesh.Vertices.push_back(VPNTBT({i + 1, j + 1, k + 1}, {qq, ww}));
        mesh.Vertices.push_back(VPNTBT({i    , j + 1, k + 1}, {q, ww}));

        mesh.Indices.push_back(c + 0);
        mesh.Indices.push_back(c + 1);
        mesh.Indices.push_back(c + 2);

        mesh.Indices.push_back(c + 2);
        mesh.Indices.push_back(c + 3);
        mesh.Indices.push_back(c + 0);
        c+=4;
        }
    }
    mesh.Unindex();
    mesh.computeNormal();
    mesh.CalcTB();
    mesh.Bind();
}

