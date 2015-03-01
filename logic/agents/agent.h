#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <memory>
#include "cereal/cereal.hpp"

#define AGENT(type)                         \
type() :                                    \
    Agent(#type, Agent::typeid_for<type>()) \
{                                           \
}                                           \
~type(){}                                   \

#define CASTER(ctype)                       \
if(agent->type == #ctype)                   \
{                                           \
    ctype *a = static_cast<ctype*>(agent);  \
    ar(cereal::make_nvp(#ctype, *a));       \
    continue;                               \
}

typedef int Jid;
typedef int Jtex;

class Agent
{
private:
    int id;

    static int next_typeid()
    {
        static int next_id(0);
        return next_id++;
    }
public:

    Agent();
    Agent(const std::string &__s, int __id);
    ~Agent();
    template <typename T_>
    static int typeid_for()
    {
        static int result(next_typeid());
        return result;
    }

    virtual Agent *instantiate() const;
    const std::string type = "EmptyAgent";
    friend class Dynamic;
    friend class BackCaster;

    template<class Archive>
    void save(Archive &ar) const
    {
      ar(CEREAL_NVP(type));
    }
};

class StaticAgent : public  Agent
{
public:
    const std::string type = "StaticAgent";
    Agent *instantiate() const;
};

#endif // AGENT_H
