#include "wins.h"
#include "component.h"
#include "sge/mouse.h"
#include "sge/helper.h"


WComponent::WComponent(WContainer *par)
{
    parent = par;
    if(parent)
        parent->Items.push_back(std::unique_ptr<WComponent>(this));
}

WComponent::~WComponent()
{

}

void WComponent::Draw() const
{

}

void WComponent::Update()
{

}

glm::vec2 WComponent::GlobalPos() const
{
    glm::vec2 p = pos;
    if(parent)
        p += parent->GlobalPos();

    switch (anchor) {
        case ANCHOR_TOP_RIGHT:
            if(parent)
                p += glm::vec2(parent->size.x, parent->header);
            return p;
        case ANCHOR_TOP_LEFT:
            if(parent)
                p += glm::vec2(0, parent->header);
            return p;
        case ANCHOR_CENTER:
            return parent->GlobalPos() + glm::vec2(0, parent->header) - size / 2.f + (parent->size - glm::vec2(0, parent->header)) / 2.f + pos;
        case ANCHOR_CENTER_HOR:
            return parent->GlobalPos() - glm::vec2(0, parent->header) - glm::vec2(size.x, 0) / 2.f + glm::vec2(parent->size.x, 0) / 2.f + pos;
        default: //ANCHOR_NO
            return pos;
    }
}


WContainer::WContainer(WContainer *par) :
    WComponent(par)
{

}

WContainer::~WContainer()
{

}

void WContainer::Draw() const
{
    WinS::sb->reduceScissor(GlobalPos() + glm::vec2(0,header), size - glm::vec2(0,header));
    for(auto &i : Items)
    {
        if(i->hidden) continue;

        i->Draw();
    }
}

void WContainer::Update()
{
    mouse_hook = false;
    for(auto &i : Items)
    {
        if(i->hidden) continue;

        i->Update();

        if(!mouse_hook && inLimsV(Mouse::GetCursorPos(), i->GlobalPos(), i->GlobalPos() + i->size))
        {
            i->aimed = true;
            if(Mouse::IsLeftPressed() && i->onLeftPress)
            {
                i->onLeftPress();
                mouse_hook = true;
            }
            if(Mouse::IsRightPressed() && i->onRightPress)
            {
                i->onRightPress();
                mouse_hook = true;
            }
        }
        else
            i->aimed = false;
    }
    WComponent::Update();
}
