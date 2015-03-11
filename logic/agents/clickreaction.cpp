#include "clickreaction.h"
#include "sge_ui/wins.h"
#include "cjarg_main_w.h"

void ClickReactionTest::Click(Block *b)
{
    auto c =  new cjarg_main_w(WinS::ws);
    c->MoveUnderCur();
}
