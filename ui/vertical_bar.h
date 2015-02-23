#ifndef VERTICAL_BAR_H
#define VERTICAL_BAR_H
#include "component.h"

class VerticalBar : public WComponent
{
public:
    VerticalBar(WContainer *par);
    ~VerticalBar();

    float top = 0.1, bot = 0.9;

    void Draw() const;
    void Update();
};

#endif // VERTICAL_BAR_H
