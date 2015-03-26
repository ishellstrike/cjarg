#ifndef DATABASE_H
#define DATABASE_H
#include "sge/logger.h"
#include <mutex>
#include "logic/map/block.h"
#include "logic/entity/item.h"
#include <unordered_map>
#include <vector>
#include "logic/map/staticblock.h"
#include "logic/entity/staticitem.h"
#include <logic/map/scheme.h>

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
            LOG(verbose) << "making database instance";
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
        LOG(verbose) << "droping database instance";
    }

    std::unordered_map<std::string, Jid> block_pointer;
    std::unordered_map<Jid, std::string> block_back_pointer;
    std::vector<std::unique_ptr<StaticBlock>> block_db;
    void registerBlock(const std::string &s, StaticBlock* b);

    std::unordered_map<std::string, Jid> item_pointer;
    std::unordered_map<Jid, std::string> item_back_pointer;
    std::vector<std::unique_ptr<StaticItem>> item_db;
    void registerItem(const std::string &s, StaticItem *i);

    std::unordered_map<SchemeType, std::vector<Scheme>> scheme_db;

    void Load();

private:
    static database *m_inst;
    database();
    ~database();
    database(const database &root) = delete;
    database &operator=(const database &) = delete;
};

#endif // DATABASE_H
