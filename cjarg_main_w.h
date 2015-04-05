#ifndef CJARG_MAIN_W_H
#define CJARG_MAIN_W_H
#include "sge_ui/win.h"
#include "sge_ui/button.h"
#include "sge_ui/label.h"
#include "sge_ui/panel.h"

class cjarg_main_w : public Win
{
public:
    cjarg_main_w(WContainer *par);
    ~cjarg_main_w();

    Label *title, *ver, *controls, *beta;
    Button *new_game, *options;
    Panel *panel;

    void Draw() const;
    void Update();

    void* operator new(size_t i)
    {
        return _mm_malloc(i,16);
    }

    void operator delete(void* p)
    {
        _mm_free(p);
    }
};

#endif // CJARG_MAIN_W_H
