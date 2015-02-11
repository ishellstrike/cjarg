#include "database.h"
#include "sge/logger.h"
#include "sge/prefecences.h"

void database::registerBlock(std::string s, StaticBlock *b)
{
    block_db.push_back(std::unique_ptr<StaticBlock>(b));
    block_back_pointer[block_db.size() - 1] = s;
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
    for(Item *item: item_db){
        delete item;
    }
}

database *database::m_inst = nullptr;
