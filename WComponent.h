#pragma once
#ifndef WComponent_h__
#define WComponent_h__
#include <glm/glm.hpp>

class WComponent {
public:
    virtual void Draw() const = 0;
    virtual void Update() = 0;
};

class WContainer : public WComponent {
public:
    virtual glm::vec2 GlobalPos() const = 0;
};
#endif // WComponent_h__
