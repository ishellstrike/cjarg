#ifndef LIST_H
#define LIST_H
#include "component.h"
#include "button.h"
#include "vertical_bar.h"

class ListContainer : public WContainer
{
public:
    ListContainer(WContainer *par);
    ~ListContainer();

    void Draw() const;
    void Update();

    int top = 0, bot = 0;

    Button *up, *down;
    VerticalBar *bar;
    const int stored_items_offset = 3;
private:
    void nolmalze_top_bot();
};

#endif // LIST_H
