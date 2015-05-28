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
#include "sge/helper.h"

class Dynamic
{
public:
    Dynamic *instantiate() const
    {
        Dynamic *dyn = new Dynamic();
        for(auto ag : agents)
        {
            dyn->agents.push_back(std::shared_ptr<Agent>(ag->instantiate()));
        }
        return dyn;
    }

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
        (void)val;
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
        {
            if(!val[s].IsInt())
                throw std::invalid_argument(string_format("value %s is not a integer", s));
            target = val[s].GetInt();
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, std::string &target)
    {
        if(val.HasMember(s))
        {
            if(!val[s].IsString())
                throw std::invalid_argument(string_format("value %s is not a string", s));
            target = val[s].GetString();
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, float &target)
    {
        if(val.HasMember(s))
        {
            if(!val[s].IsNumber())
                throw std::invalid_argument(string_format("value %s is not a number", s));
            target = static_cast<float>(val[s].GetDouble());
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, bool &target)
    {
        if(val.HasMember(s))
        {
            if(!val[s].IsBool_())
                throw std::invalid_argument(string_format("value %s is not a bool", s));
            target = val[s].GetBool_();
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, glm::vec2 &target)
    {
        if(val.HasMember(s) && val[s].IsArray())
        {
            const rapidjson::Value &arr = val[s];
            if(arr.Size() != 2)          throw std::invalid_argument(string_format("value %s is not vec2", s));
            if(!arr.Begin()->IsNumber()) throw std::invalid_argument(string_format("value %s[0] is not a number", s));
            if(!arr[1].IsNumber())       throw std::invalid_argument(string_format("value %s[1] is not a number", s));

            target.x = static_cast<float>(arr.Begin()->GetDouble());
            target.y = static_cast<float>(arr[1].GetDouble());
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, glm::vec3 &target)
    {
        if(val.HasMember(s) && val[s].IsArray())
        {
            const rapidjson::Value &arr = val[s];
            if(arr.Size() != 3)          throw std::invalid_argument("value is not vec3");
            if(!arr.Begin()->IsNumber()) throw std::invalid_argument(string_format("value %s[0] is not a number", s));
            if(!arr[1].IsNumber())       throw std::invalid_argument(string_format("value %s[1] is not a number", s));
            if(!arr[2].IsNumber())       throw std::invalid_argument(string_format("value %s[2] is not a number", s));

            target.x = static_cast<float>(arr.Begin()->GetDouble());
            target.y = static_cast<float>(arr[1].GetDouble());
            target.z = static_cast<float>(arr[2].GetDouble());
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, glm::vec4 &target)
    {
        if(val.HasMember(s) && val[s].IsArray())
        {
            const rapidjson::Value &arr = val[s];
            if(arr.Size() != 4)          throw std::invalid_argument("target variable is not vec4");
            if(!arr.Begin()->IsNumber()) throw std::invalid_argument(string_format("value %s[0] is not a number", s));
            if(!arr[1].IsNumber())       throw std::invalid_argument(string_format("value %s[1] is not a number", s));
            if(!arr[2].IsNumber())       throw std::invalid_argument(string_format("value %s[2] is not a number", s));
            if(!arr[3].IsNumber())       throw std::invalid_argument(string_format("value %s[3] is not a number", s));

            target.x = static_cast<float>(arr.Begin()->GetDouble());
            target.y = static_cast<float>(arr[1].GetDouble());
            target.z = static_cast<float>(arr[2].GetDouble());
            target.w = static_cast<float>(arr[3].GetDouble());
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<int> &target)
    {
        if(val.HasMember(s))
        {
            const rapidjson::Value &arr = val[s];
            if(!arr.IsArray())
                throw std::invalid_argument("target variable is not array");
            for(decltype(arr.Size()) i = 0; i < arr.Size(); i++)
            {
                if(!arr[i].IsInt())
                    throw std::invalid_argument(string_format("value %s[%d] is not a integer", s, i));
                target.push_back(arr[i].GetInt());
            }
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<std::string> &target)
    {
        if(val.HasMember(s) && val[s].IsArray())
        {
            const rapidjson::Value &arr = val[s];
            if(!arr.IsArray())
                throw std::invalid_argument("target variable is not array");
            for(decltype(arr.Size()) i = 0; i < arr.Size(); i++)
            {
                if(!arr[i].IsString())
                    throw std::invalid_argument(string_format("value %s[%d] is not a string", s, i));
                target.push_back(arr[i].GetString());
            }
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<bool> &target)
    {
        if(val.HasMember(s) && val[s].IsArray())
        {
            const rapidjson::Value &arr = val[s];
            if(!arr.IsArray())
                throw std::invalid_argument("target variable is not array");
            for(decltype(arr.Size()) i = 0; i < arr.Size(); i++)
            {
                if(!arr[i].IsBool_())
                    throw std::invalid_argument(string_format("value %s[%d] is not a bool", s, i));
                target.push_back(arr[i].GetBool_());
            }
        }
    }

    static void __deserialize(const rapidjson::Value &val, const char *s, std::vector<float> &target)
    {
        if(val.HasMember(s) && val[s].IsArray())
        {
            const rapidjson::Value &arr = val[s];
            if(!arr.IsArray()) throw std::invalid_argument("target variable is not array");
            for(decltype(arr.Size()) i = 0; i < arr.Size(); i++)
            {
                if(!arr[i].IsDouble())
                    throw std::invalid_argument(string_format("value %s[%d] is not a number", s, i));
                target.push_back(static_cast<float>(arr[i].GetDouble()));
            }
        }
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
