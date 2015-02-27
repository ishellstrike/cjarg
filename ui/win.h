#ifndef Win_h__
#define Win_h__
#include <glm/glm.hpp>
#include "component.h"
#include <vector>
#include <string>
#include <memory>
#include "button.h"

class Win : public WContainer
{
public:
    Win(WContainer *par);
    virtual ~Win();
    virtual void Draw() const;
    void Update();
    glm::vec2 drag_point;
    bool dragged = false;
    bool resizing = false;
    glm::vec2 resize_point;
    void MoveUnderCur();

    glm::vec4 col;
    std::string text;

    Button *closeb;
};

#endif // Win_h__

