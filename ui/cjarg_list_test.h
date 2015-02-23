#ifndef CJARG_LIST_TEST_H
#define CJARG_LIST_TEST_H
#include "win.h"
#include "list_container.h"

class cjarg_list_test : public Win
{
public:
    cjarg_list_test(WContainer *par);
    ~cjarg_list_test();

    ListContainer *lc;
    ListContainer *lc2;

    void Draw() const;
    void Update();
};

#endif // CJARG_LIST_TEST_H
