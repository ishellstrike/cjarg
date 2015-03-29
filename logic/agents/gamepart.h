#ifndef GAMEPART_H
#define GAMEPART_H
#include <vector>
#include <memory>
#include <functional>
#include "../agents/agent.h"
#include "rapidjson/document.h"
#include <string>
#include <sstream>
#include "sge/logger.h"

class Dynamic
{
public:
    Dynamic *instantiate() const;

    template <typename T>
    T *getAgent()
    {
        for(auto a : agents)
        {
            Agent &agent = *a;
            if(agent.id == Agent::typeid_for<T>())
                return static_cast<T*>(&agent);
        }
        return nullptr;
    }

    template <typename T>
    bool hasAgent()
    {
        for(auto a : agents)
        {
            Agent &agent = *a;
            if(agent.id == Agent::typeid_for<T>())
                return true;
        }
        return false;
    }

    template <typename T>
    bool forAgent(std::function<void(T*)> a)
    {
        T *agent = getAgent<T>();
        if(agent)
        {
            a(agent->agent);
            return true;
        }
        return false;
    }

    template <typename T>
    void pushAgent(std::shared_ptr<T> agent)
    {
        agents.push_back(agent);
    }

    bool isEmpty()
    {
        return agents.size() == 0;
    }

    std::string debugInfo()
    {
        std::stringstream ss;

        for(std::shared_ptr<Agent> ag : agents)
        {
            ss << "{" << ag->debugInfo() << "} ";
        }

        return ss.str();
    }

    std::string fullInfo()
    {
        std::stringstream ss;

        for(std::shared_ptr<Agent> ag : agents)
            ss << ag->fullInfo() << ". ";

        return ss.str();
    }

private:
    std::vector<std::shared_ptr<Agent>> agents;
};

#define DEBUGINFO(target) DebugToStringHelper::debugInfo(#target, target)

struct DebugToStringHelper {
    template<typename Ty_>
    static std::string debugInfo(char *s, Ty_ &target)
    {
        std::stringstream ss;
        ss << s << ": " << std::to_string(target) << "; ";
        return ss.str();
    }

    template<>
    static std::string debugInfo(char *s, std::string &target)
    {
        std::stringstream ss;
        ss << s << ": \"" << target << "\"; ";
        return ss.str();
    }
};

#define DESERIALIZE(target) DeserializeHelper::deserialize(val, #target, target)

struct DeserializeHelper {
    static void deserialize(const rapidjson::Value &val, char *s, int &target)
    {
        if(val.HasMember(s))
            target = val[s].GetInt();
    }

    static void deserialize(const rapidjson::Value &val, char *s, std::string &target)
    {
        if(val.HasMember(s))
            target = val[s].GetString();
    }

    static void deserialize(const rapidjson::Value &val, char *s, float &target)
    {
        if(val.HasMember(s))
            target = static_cast<float>(val[s].GetDouble());
    }

    static void deserialize(const rapidjson::Value &val, char *s, bool &target)
    {
        if(val.HasMember(s))
            target = val[s].GetBool_();
    }
};

struct GameBase {
    std::unique_ptr<Dynamic> parts = nullptr;

    Jid id = 0;
};

struct Static
{
    std::vector<std::shared_ptr<StaticAgent>> static_agents;
};

#endif // GAMEPART_H
