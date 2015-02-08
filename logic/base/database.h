#ifndef DATABASE_H
#define DATABASE_H
#include "sge/logger.h"
#include <mutex>
#include "logic/map/block.h"
#include "logic/entity/item.h"
#include <unordered_map>

class database
{
public:
public:
    static database *instance()
    {
        static std::mutex mutex;
        if(!m_inst)
        {
            mutex.lock();

            if (!m_inst)
                m_inst = new database();

            mutex.unlock();
            LOG(info) << "making database instance";
        }
        return m_inst;
    }

    static void drop()
    {
        static std::mutex mutex;
        mutex.lock();
        if(m_inst)
        {
            delete m_inst;
            m_inst = nullptr;
        }
        mutex.unlock();
        LOG(info) << "droping database instance";
    }

    std::unordered_map<std::string, Jid> block_pointer;
    std::vector<Block*> block_db;
    void registerBlock(std::string s, Block* b);

    std::unordered_map<std::string, Jid> item_pointer;
    std::vector<Item*> item_db;
    void registerItem(std::string s, Item* i);

    void Load();

private:
    static database *m_inst;
    database();
    ~database();
    database(const database &root){}
    database &operator=(const database &){}
};

#endif // DATABASE_H
