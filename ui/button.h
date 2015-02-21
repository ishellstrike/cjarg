#ifndef BUTTON_H
#define BUTTON_H
#include "component.h"
#include <glm/glm.hpp>
#include <functional>

class Button : public WComponent
{
public:
    Button(WContainer *par);
    ~Button();

    void Draw() const;
    void Update();
    glm::vec2 size = glm::vec2(50,20);
    std::string text;
};

#endif // BUTTON_H
