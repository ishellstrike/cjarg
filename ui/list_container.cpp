#include "list_container.h"
#include "wins.h"
#include "sge/colorextender.h"
#include "label.h"

ListContainer::ListContainer(WContainer *par) :
    WContainer(par)
{
    for(int i=0;i<10;i++)
    {
        auto l = new Label(this);
        l->text = "test";
    }
}

ListContainer::~ListContainer()
{

}

void ListContainer::Draw() const
{
    glm::vec2 p = GlobalPos();
    int ii = 0;
    for(auto &i : Items)
    {
        (*i).pos = {0, ii*20};
        ii++;
    }
    WContainer::Draw();
}

void ListContainer::Update()
{
    WContainer::Update();
}
