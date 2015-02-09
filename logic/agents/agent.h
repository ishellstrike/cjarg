#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <memory>

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

    template <typename T_>
    static int typeid_for()
    {
        static int result(next_typeid());
        return result;
    }

    virtual Agent* instantiate() const = 0;
    const std::string type = "Agent";
};


class StaticAgent : public  Agent
{
public:
    const std::string type = "StaticAgent";
    Agent *instantiate() const;
};

#endif // AGENT_H
