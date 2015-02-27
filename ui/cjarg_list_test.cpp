#include "cjarg_list_test.h"

cjarg_list_test::cjarg_list_test(WContainer *par) :
    Win(par)
{
    lc = new ListContainer(this);
    lc->pos = {10,10};
    lc->size = {100,100};

    size = {200, 200};
}

cjarg_list_test::~cjarg_list_test()
{

}

void cjarg_list_test::Draw() const
{
    Win::Draw();
}

void cjarg_list_test::Update()
{
    lc->size = size - glm::vec2(20,20+header);
    Win::Update();
}

