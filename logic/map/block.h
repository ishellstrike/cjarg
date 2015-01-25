#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include "agents/agent.h"
typedef int Jid;
typedef int Jtex;

class Block
{
public:
    Block();
    /*!
     * \brief Using for create database examples
     * \param a
     * \param agents_
     */
    Block(int a, std::vector<Caster> agents_);
    ~Block();

    Jid id();
    Jid tex();

    void id(Jid id_);
    void tex(Jid tex_);

    template <typename T>
    T *getAgent(){
        for(Caster c: agents)
        {
            if(c.is<T>())
                return &c.as<T>();
        }
        return nullptr;
    }

private:
    Jid m_id = 0;
    Jtex m_tex = 0;

    std::vector<Caster> agents;
};

#endif // BLOCK_H
