#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <memory>
#include "rapidjson/document.h"

#define AGENT(type)                         \
type() :                                    \
    Agent(#type, Agent::typeid_for<type>()) \
{                                           \
}                                           \
~type(){}                                   \

#define CASTER(ctype)   \
if(strcmp(part["type"].GetString(), #ctype) == 0) \
{ \
    std::shared_ptr<ctype> c =  std::make_shared<ctype>(); \
    c->deserialize(part); \
    b->etalon->parts->agents.push_back(c); \
} \
else


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

    void deserialize(rapidjson::Value &val);
};

class StaticAgent : public  Agent
{
public:
    const std::string type = "StaticAgent";
    Agent *instantiate() const;
};

#endif // AGENT_H
