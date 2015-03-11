#ifndef CJARG_PERFOMANCE_H
#define CJARG_PERFOMANCE_H
#include "sge_ui/wins.h"
#include "sge_ui/wins.h"
#include "sge/fpscounter.h"
#include "sge/gametimer.h"
#include <list>
#include "sge_ui/graph.h"

class cjarg_perfomance : public Win
{
public:
    cjarg_perfomance(WContainer *par);

    void Draw() const;
    void Update();
    void UpdateTimer(const FPSCounter &fps, const GameTimer &gt);
    Graph *gfps, *ggt, *gfps_fast, *ggt_fast;
    float fastsec = 0;
    float compose_fps = 0, compose_gt = 0;
    int compose = 0;
};

#endif // CJARG_PERFOMANCE_H
