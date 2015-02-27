#include "clickreaction.h"
#include "ui/wins.h"
#include "ui/cjarg_main_w.h"

void ClickReactionTest::Click(Block *b)
{
    auto c =  new cjarg_main_w(WinS::ws);
    c->MoveUnderCur();
}
