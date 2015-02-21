#ifndef LIST_H
#define LIST_H
#include "component.h"

class ListContainer : public WContainer
{
public:
    ListContainer(WContainer *par);
    ~ListContainer();

    void Draw() const;
    void Update();
};

#endif // LIST_H
