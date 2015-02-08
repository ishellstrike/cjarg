#include "database.h"
#include "sge/logger.h"
#include "sge/prefecences.h"

void database::registerBlock(std::string s, Block *b)
{
    block_db.push_back(b);
    block_pointer[s] = block_db.size() - 1;
    //LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

void database::registerItem(std::string s, Item *i)
{
    item_db.push_back(i);
    item_pointer[s] = item_db.size() - 1;
    //LOG(info) << "register \"" << s << "\" as " << block_db.size() - 1;
}

void database::Load()
{

}

database::database()
{

}

database::~database()
{
    for(Block* block: block_db){
        delete block;
    }
    for(Item* item: item_db){
        delete item;
    }
}

database *database::m_inst = nullptr;
