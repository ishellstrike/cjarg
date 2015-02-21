#include "cjarg_list_test.h"

cjarg_list_test::cjarg_list_test(WContainer *par) :
    Win(par)
{
    lc = new ListContainer(this);
}

cjarg_list_test::~cjarg_list_test()
{

}

