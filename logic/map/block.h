#ifndef BLOCK_H_
#define BLOCK_H_
#include <vector>
#include <logic/agents/gamepart.h>

struct Block
{
    Jid id();

    void id(Jid id_);

    std::unique_ptr<Dynamic> parts = nullptr;

    Block(){}
    ~Block(){}
    Block(const Block&) = delete;
    Block& operator=(const Block&) = delete;

    Jid m_id = 0;
    Jtex m_tex = 0;
};

#endif // BLOCK_H_
