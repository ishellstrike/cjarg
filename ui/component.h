#pragma once
#ifndef WComponent_h__
#define WComponent_h__
#include <glm/glm.hpp>
#include <vector>
#include <memory>
#include "wcontainer.h"
#include <functional>

class WContainer;
class WComponent {
public:
    enum ANCHOR
    {
        ANCHOR_TOP_LEFT,
        ANCHOR_TOP_RIGHT,
        ANCHOR_CENTER,
        ANCHOR_CENTER_HOR,
        ANCHOR_NO
    };

    WComponent(WContainer *par = nullptr);
    virtual ~WComponent();
    virtual void Draw() const = 0;
    virtual void Update() = 0;
    glm::vec2 GlobalPos() const;
    WContainer *parent;

    glm::vec2 pos;
    glm::vec2 size = {100,100};
    bool hidden = false;
    bool aimed = false;
    float header = 0;

    ANCHOR anchor = ANCHOR_TOP_LEFT;
    std::function<void()> onRightPress, onLeftPress;
};

class WContainer : public WComponent {
public:
    WContainer(WContainer *par = nullptr);
    virtual ~WContainer();
    std::vector<std::unique_ptr<WComponent>> Items;
    bool mouse_hook = false;

    virtual void Draw() const;
    virtual void Update();
};
#endif // WComponent_h__
