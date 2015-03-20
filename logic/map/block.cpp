#include "block.h"
#include "logic/base/database.h"
#include "sge/textureatlas.h"
Jid Block::id()
{
    return m_id;
}
void Block::id(Jid id_)
{
    m_id = id_;
}
