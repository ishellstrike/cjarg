#include "block.h"
#include "logic/base/database.h"

Block::Block()
{

}

Block::~Block()
{

}

int Block::id()
{
    return m_id;
}

int Block::tex()
{
    return m_tex;
}

void Block::id(int id_)
{
    m_id = id_;
}

void Block::tex(int tex_)
{
    m_tex = tex_;
}

