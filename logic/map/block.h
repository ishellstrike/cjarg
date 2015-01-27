#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <logic/agents/gamepart.h>
#include "../agents/agent.h"
typedef int Jid;
typedef int Jtex;

class Block : public GamePart
{
public:
    Block();
    /*!
     * \brief Using for create database examples
     * \param a
     * \param agents_
     */
    Block(std::vector<Caster> agents_, Jtex a);
    ~Block();

    Jid id();
    Jid tex();

    void id(Jid id_);
    void tex(Jid tex_);

private:
    Jid m_id = 0;
    Jtex m_tex = 0;
};

#endif // BLOCK_H
