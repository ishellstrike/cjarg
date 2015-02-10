#include "block.h"
#include "logic/base/database.h"

Block::Block()
{
}

Block::Block(const std::vector<Agent*> &agents_, const std::string &id)
{
   parts = new Dynamic();
   for(Agent* ag : agents_)
   {
       parts->agents.push_back(std::shared_ptr<Agent>(ag));
   }
}

Block::~Block()
{
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
