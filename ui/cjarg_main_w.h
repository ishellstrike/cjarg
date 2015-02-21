#ifndef CJARG_MAIN_W_H
#define CJARG_MAIN_W_H
#include "win.h"
#include "button.h"
#include "label.h"
#include "panel.h"

class cjarg_main_w : public Win
{
public:
    cjarg_main_w(WContainer *par);
    ~cjarg_main_w();

    Label *title;
    Button *new_game, *options;
    Panel *panel;
};

#endif // CJARG_MAIN_W_H
