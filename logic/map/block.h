#ifndef BLOCK_H
#define BLOCK_H
#include <vector>
#include "agents/agent.h"

class Block
{
public:
    Block();
    ~Block();

    int id();
    int tex();

    void id(int id_);
    void tex(int tex_);
private:
    int m_id = 0;
    int m_tex = 0;

    std::vector<Agent*> agents;
};

#endif // BLOCK_H
