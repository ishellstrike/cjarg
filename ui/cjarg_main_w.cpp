#include "cjarg_main_w.h"

cjarg_main_w::cjarg_main_w(WContainer *par) :
    Win(par)
{
    text = "Main Window";

    panel = new Panel(this);
    panel->anchor = ANCHOR_CENTER;
    panel->size = {150, 150};

    new_game = new Button(panel);
    new_game->anchor = ANCHOR_CENTER;
    new_game->size = {100,20};
    new_game->text = "New game";

    options = new Button(panel);
    options->anchor = ANCHOR_CENTER;
    options->size = {100,20};
    options->pos = {0, 30};
    options->text = "Options";

    title = new Label(panel);
    title->text = "Label";
    title->pos = {3, 3};
    title->anchor = ANCHOR_TOP_LEFT;
}

cjarg_main_w::~cjarg_main_w()
{

}

