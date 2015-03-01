#include "block.h"
#include "logic/base/database.h"
#include "sge/textureatlas.h"

Block::Block()
{
}

Block::Block(const std::vector<Agent*> &agents_, const std::string &id)
{
   parts = std::unique_ptr<Dynamic>(new Dynamic());
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
void Block::id(Jid id_)
{
    m_id = id_;
}
