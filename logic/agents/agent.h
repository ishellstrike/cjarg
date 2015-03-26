#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <memory>
#include "rapidjson/document.h"
#include "sge/gametimer.h"
#include <glm/glm.hpp>
#include "../../tests/catch.hpp"

class Level;

#define AGENT(type)                         \
type() :                                    \
    Agent(#type, Agent::typeid_for<type>()) \
{                                           \
}                                           \
~type(){}                                   \
type(const type&) = delete;                 \
type& operator=(const type&) = delete;

#define CASTER(ctype)                                      \
if(strcmp(part["type"].GetString(), #ctype) == 0)          \
{                                                          \
    std::shared_ptr<ctype> c = std::make_shared<ctype>();  \
    c->deserialize(part);                                  \
    b->etalon->parts->pushAgent(c);                        \
} else


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

    const std::string type = "EmptyAgent";
    friend class Dynamic;

    virtual void deserialize(rapidjson::Value &val) = 0;

    virtual Agent *instantiate() const = 0;
    virtual void Update(const GameTimer &gt, const glm::vec3 &pos, const Level &l) = 0;
    virtual void Init(const glm::vec3 &pos, const Level &l) = 0;
};

class StaticAgent : public  Agent
{
public:
    const std::string type = "StaticAgent";
    Agent *instantiate() const;
};

#endif // AGENT_H
