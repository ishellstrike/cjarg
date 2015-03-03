#ifndef GRAPH_H
#define GRAPH_H
#include "win.h"
#include <vector>

class Graph : public WComponent
{
public:
    Graph(WContainer *par);

    void Draw() const;
    void Update();
    void AddValue(float a);

    std::vector<float> data;
    int dpos;
    float min = 0, max = 100;
    const int dsize = 100;
};

#endif // GRAPH_H
