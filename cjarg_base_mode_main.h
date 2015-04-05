#ifndef CJARG_BASE_MODE_MAIN_H
#define CJARG_BASE_MODE_MAIN_H
#include "sge_ui/win.h"
#include "sge_ui/list_container.h"
#include "sge_ui/button.h"

class cjarg_base_mode_main : public Win
{
public:
    cjarg_base_mode_main(WContainer *par);
    ~cjarg_base_mode_main();

    enum ORD {
        ORD_DIG,
        ORD_BUILD,
        ORD_RPG
    };

    Button *build, *dig;
    ORD current_order;

    void Draw() const;
    void Update();

    ORD GetCurOrder();

    void* operator new(size_t i)
    {
        return _mm_malloc(i,16);
    }

    void operator delete(void* p)
    {
        _mm_free(p);
    }
};

#endif // CJARG_BASE_MODE_MAIN_H
