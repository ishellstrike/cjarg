#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <logic/agents/gamepart.h>
#include "../agents/agent.h"

class Block
{
public:
    Block();
    /*!
     * \brief Using for create database examples
     * \param a
     * \param agents_
     */
    Block(const std::vector<Agent *> &agents_, const std::string &id);
    ~Block();

    Jid id();

    void id(Jid id_);

    Dynamic *parts = nullptr;

private:
    Jid m_id = 0;
    Jtex m_tex = 0;
};

#endif // BLOCK_H
