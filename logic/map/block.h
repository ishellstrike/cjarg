#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <logic/agents/gamepart.h>
#include "../agents/agent.h"
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
    Block(std::vector<Agent *> &&agents_, const std::string &id);
    ~Block();

    Jid id();
    Jtex tex();

    void id(Jid id_);
    void tex(Jid tex_);

    Dynamic *parts;

private:
    Jid m_id = 0;
    Jtex m_tex = 0;
};

#endif // BLOCK_H
