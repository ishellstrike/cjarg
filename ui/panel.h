#ifndef PANEL_H
#define PANEL_H
#include "component.h"

class Panel : public WContainer
{
public:
    Panel(WContainer *par);
    ~Panel();

    void Draw() const;
    void Update();
};

#endif // PANEL_H
