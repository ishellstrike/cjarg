#pragma once
#ifndef WComponent_h__
#define WComponent_h__
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "wcontainer.h"
#include <functional>
#include "sge/colorextender.h"

class WContainer;
class WComponent {
public:
    enum ANCHOR
    {
        ANCHOR_TOP_LEFT,
        ANCHOR_TOP_RIGHT,
        ANCHOR_DOWN_LEFT,
        ANCHOR_DOWN_RIGHT,
        ANCHOR_CENTER,
        ANCHOR_CENTER_HOR,
        ANCHOR_NO
    };

    WComponent(WContainer *par = nullptr);
    virtual ~WComponent();
    virtual void Draw() const = 0;
    virtual void Update() = 0;
    glm::vec2 globalPos() const;
    WContainer *parent;

    glm::vec2 pos;
    glm::vec2 size;
    glm::vec4 color = Color::White;
    glm::vec4 aimed_color = Color::White;

    ANCHOR anchor = ANCHOR_TOP_LEFT;
    std::function<void()> onRightPress, onLeftPress;
    std::function<void()> onWheelUp, onWheelDown;
    bool hidden = false;
    bool aimed = false;
    float header = 0;
};

class WContainer : public WComponent {
    friend class WComponent;
public:
    WContainer(WContainer *par = nullptr);
    virtual ~WContainer();

    virtual void Draw() const;
    virtual void Update();

protected:
    std::vector<std::unique_ptr<WComponent>> Items;
    bool mouse_hook = false;
};
#endif // WComponent_h__
