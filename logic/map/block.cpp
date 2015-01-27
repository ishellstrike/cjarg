#include "block.h"
#include "logic/base/database.h"

Block::Block()
{

}

Block::Block(std::vector<Caster> agents_, int a)
{
   agents = agents_;
}

Block::~Block()
{
}

Jid Block::id()
{
    return m_id;
}

Jid Block::tex()
{
    return m_tex;
}

void Block::id(Jid id_)
{
    m_id = id_;
}

void Block::tex(Jid tex_)
{
    m_tex = tex_;
}
