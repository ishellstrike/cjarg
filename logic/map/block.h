#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include <logic/agents/gamepart.h>
#include "../agents/agent.h"

class Block
{
public:
    Jid id();

    void id(Jid id_);

    std::unique_ptr<Dynamic> parts = nullptr;

    Jid m_id = 0;
    Jtex m_tex = 0;
};

#endif // BLOCK_H
