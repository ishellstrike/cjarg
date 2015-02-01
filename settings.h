#ifndef SETTINGS_H
#define SETTINGS_H

#include <mutex>
#include <glm/glm.hpp>
#include "sge/logger.h"

#define RESX (int)Settings::instance()->resolution.x
#define RESY (int)Settings::instance()->resolution.y

class Settings
{
public:
    static Settings *instance()
    {
        static std::mutex mutex;
        if(!m_inst)
        {
            mutex.lock();

            if (!m_inst)
                m_inst = new Settings();

            mutex.unlock();
            LOG(info) << "making settings instance";
        }
        return m_inst;
    }

    static void drop()
    {
        static std::mutex mutex;
        mutex.lock();
        delete m_inst;
        m_inst = nullptr;
        mutex.unlock();
        LOG(info) << "droping settings instance";
    }
    glm::vec2 resolution = glm::vec2(800, 600);
private:
    static Settings *m_inst;
    Settings();
    ~Settings();
    Settings(const Settings &root);
    Settings &operator=(const Settings &);
};

#endif // SETTINGS_H
