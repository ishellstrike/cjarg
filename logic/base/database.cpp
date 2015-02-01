#include "database.h"
#include "sge/logger.h"

void database::registerBlock(std::string s, Block *b)
{
    block_db.push_back(b);
    block_pointer[s] = block_db.size() - 1;
    LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

database *database::m_inst = nullptr;
