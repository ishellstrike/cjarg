#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <memory>

class AgentBase
{
private:
    int id;

    static int next_typeid()
    {
        static int static_id(0);
        return static_id++;
    }
public:

    template <typename T_>
    static int typeid_for()
    {
        static int result(next_typeid());
        return result;
    }
};

class Agent : public  AgentBase
{
public:


    virtual Agent* instantiate();
    static const std::string type = "Agent";
};


class StaticAgent : public  AgentBase
{
public:
    static const std::string type = "StaticAgent";
};

#endif // AGENT_H
