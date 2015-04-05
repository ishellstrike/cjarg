#include "cjarg_base_mode_main.h"
#include "sge/prefecences.h"

cjarg_base_mode_main::cjarg_base_mode_main(WContainer *par) :
    Win(par)
{
    text = "Base builder";
    closeb->hidden = true;

    dig = new Button(this);
    dig->anchor = ANCHOR_CENTER_HOR;
    dig->pos = {0, 50 + 30*0};
    dig->size = {100,20};
    dig->text = "выкопать";
    dig->onLeftPress = [&](){current_order = ORD_DIG;};

    build = new Button(this);
    build->anchor = ANCHOR_CENTER_HOR;
    build->pos = {0, 50 + 30*1};
    build->size = {100,20};
    build->text = "построить";
    build->onLeftPress = [&](){current_order = ORD_BUILD;};

    movable = false;
    resizable = false;
}

cjarg_base_mode_main::~cjarg_base_mode_main()
{

}

void cjarg_base_mode_main::Draw() const
{
    Win::Draw();
}

void cjarg_base_mode_main::Update()
{
    pos = {RESX - size.x, 0};
    size = {130, RESY - 2};
    Win::Update();
}

cjarg_base_mode_main::ORD cjarg_base_mode_main::GetCurOrder()
{
    if(hidden) return ORD_RPG;
    return current_order;
}

