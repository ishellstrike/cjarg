#include "block.h"
#include "logic/base/database.h"
#include "sge/textureatlas.h"

std::shared_ptr<Block> Block::instantiate()
{
    std::shared_ptr<Block> c = std::make_shared<Block>();

    ao_this.n = AgentOwner::CREATURE;

    if(parts)
        c->parts = std::unique_ptr<Dynamic>(parts->instantiate());
    c->m_id = m_id;

    return c;
}

std::string Block::debugInfo()
{
    std::stringstream s;
    s << "block " << m_id << "\n";
    if(parts) {
        s << parts->debugInfo() << "\n";
    }
    s << "\n";

    return s.str();
}
