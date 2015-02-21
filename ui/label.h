#ifndef LABEL_H
#define LABEL_H
#include "component.h"
#include <glm/glm.hpp>

class Label : public WComponent
{
public:
    Label(WContainer *par);
    ~Label();
    std::string text;
public:
    void Draw() const;
    void Update();
};

#endif // LABEL_H
