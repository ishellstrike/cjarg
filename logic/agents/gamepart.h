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
#include <utility>

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
    static std::string debugInfo(const char *s, Ty_ &target)
    {
        std::stringstream ss;
        ss << s << ": " << std::to_string(target) << "; ";
        return ss.str();
    }

    static std::string debugInfo(const char *s, std::string &target)
    {
        std::stringstream ss;
        ss << s << ": \"" << target << "\"; ";
        return ss.str();
    }
};

struct DeserializeHelper {
    template <class T>
    inline static std::pair<const char *, T> make_nvp(const char *name, T &&value) {
        return{name, std::forward<T>(value)};
    }

#define NVP(T) DeserializeHelper::make_nvp(#T, T)
#define DESERIALIZE(...) DeserializeHelper::deserialize(val, __VA_ARGS__)

    static void deserialize(const rapidjson::Value &val) {
    }

    template <typename Last>
    static void deserialize(const rapidjson::Value &val, const Last &last) {
        __deserialize(val, last.first, last.second);
    }

    template <typename First, typename... Rest>
    static void deserialize(const rapidjson::Value &val, const First &first, const Rest&... rest) {
        __deserialize(val, first.first, first.second);
        deserialize(val, rest...);
    }

private:
    static void __deserialize(const rapidjson::Value &val, const char *s, int &target)
    {
        if(val.HasMember(s))
            target = val[s].GetInt();
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, std::string &target)
    {
        if(val.HasMember(s))
            target = val[s].GetString();
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, float &target)
    {
        if(val.HasMember(s))
            target = static_cast<float>(val[s].GetDouble());
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, bool &target)
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
