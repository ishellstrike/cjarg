#include "block.h"
#include "logic/base/database.h"

Block::Block()
{
}

Block::Block(std::vector<Agent*> &&agents_, const std::string &id)
{
   parts = new Dynamic();
   parts->agents = agents_;
}

Block::~Block()
{
    if(parts)
        delete parts;
}

Jid Block::id()
{
    return m_id;
}

Jtex Block::tex()
{
    return m_tex;
}

void Block::id(Jid id_)
{
    m_id = id_;
}

void Block::tex(Jtex tex_)
{
    m_tex = tex_;
}
