#ifndef DATABASE_H
#define DATABASE_H
#include "logger.h"
#include <mutex>

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

private:
    static database *m_inst;
    database(){}
    ~database(){}
    database(const database &root){}
    database &operator=(const database &){}
};

#endif // DATABASE_H
