#include "cjarg_main_w.h"
#include "sge/helper.h"

cjarg_main_w::cjarg_main_w(WContainer *par) :
    Win(par)
{
    text = "Main Window";

    size = {800, 600};

    panel = new Panel(this);
    panel->anchor = ANCHOR_CENTER;
    panel->size = {700,500};

    new_game = new Button(panel);
    new_game->anchor = ANCHOR_CENTER;
    new_game->size = {100,20};
    new_game->text = "New game";
    new_game->pos = {0, 30};
    new_game->onLeftPress = [=](){hidden = true;};

    options = new Button(panel);
    options->anchor = ANCHOR_CENTER;
    options->size = {100,20};
    options->pos = {0, 60};
    options->text = "Options";

    title = new Label(panel);
    title->text(R"lim(
     __
    |__|____ _______  ____
    |  \__  \\_  __ \/ ___\
    |  |/ __ \|  | \/ /_/  >
/\__|  (____  /__|  \___  /
\______|    \/     /_____/    )lim");
    title->pos = {0, 0};
    title->anchor = ANCHOR_CENTER_HOR;

    ver = new Label(panel);
    ver->pos = {0, title->pos.y + title->size.y + 10};
    ver->anchor = ANCHOR_CENTER_HOR;
    ver->text(string_format("cjarg %s %s", "v", "d"));

    controls = new Label(panel);
    controls->pos = {0, ver->pos.y + ver->size.y + 10};
    controls->anchor = ANCHOR_CENTER_HOR;
    controls->text("I-inventory C-caracter page L-event log \n"
                   "M-map WASD-moving LMB-shooting \n"
                   "F1-debug info O-statistic P-achievements");

    beta = new Label(panel);
    beta->pos = {0, controls->pos.y + controls->size.y + 10};
    beta->anchor = ANCHOR_CENTER_HOR;
    beta->text("Jarg now in early development. \n"
               "It's tottaly free and opensource. \n"
               "Please send your suggestions to ishellstrike@gmail.com \n"
               "or http://github.com/ishellstrike/cjarg/issues.");
}

cjarg_main_w::~cjarg_main_w()
{

}

void cjarg_main_w::Draw() const
{
    Win::Draw();
}

void cjarg_main_w::Update()
{
    Win::Update();
}

