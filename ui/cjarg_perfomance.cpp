#include "cjarg_perfomance.h"

cjarg_perfomance::cjarg_perfomance(WContainer *par) :
    Win(par)
{
    size = {200,220};
    pos = {200,0};

    ggt = new Graph(this);
    gfps = new Graph(this);
    gfps->pos = {100,0};

    ggt_fast = new Graph(this);
    gfps_fast = new Graph(this);
    ggt_fast->pos = {0,100};
    gfps_fast->pos = {100,100};
}

void cjarg_perfomance::Draw() const
{
    Win::Draw();
}

void cjarg_perfomance::Update()
{
    Win::Update();
}

void cjarg_perfomance::UpdateTimer(const FPSCounter &fps, const GameTimer &gt)
{
    fastsec += gt.elapsed;

    if(fastsec > 0.01)
    {
        ggt_fast->AddValue(gt.elapsed);
        gfps_fast->AddValue(fps.GetCount());
        fastsec = 0;
        compose_fps += fps.GetCount();
        compose_gt += gt.elapsed;
        compose ++;
        if(compose >= 9)
        {
            ggt->AddValue(compose_gt/10.f);
            gfps->AddValue(compose_fps/10.f);
            compose_fps = 0;
            compose_gt = 0;
            compose = 0;
        }
    }
}
