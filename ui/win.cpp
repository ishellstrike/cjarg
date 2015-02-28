#include "ui/win.h"
#include <glm/glm.hpp>
#include "ui/wins.h"
#include "sge/mouse.h"
#include <vector>
#include "sge/colorextender.h"
#include "sge/helper.h"
#include "sge/prefecences.h"

Win::Win(WContainer *par) :
    col(0,0,0,0.75),
    WContainer(par)
{
    closeb = new Button(this);
    closeb->text = "X";
    closeb->size = {20,20};
    closeb->anchor = ANCHOR_TOP_RIGHT;
    closeb->pos = {-20, -20};
    closeb->onLeftPress = [&](){hidden = true;};
    header = 20;

    size = {200,200};
}

Win::~Win()
{
}

void Win::Draw() const
{
    SpriteBatch& sb = *WinS::sb;

    sb.drawRect(pos, size, col);
    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, Color::White);

    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, Color::White);
    sb.drawLine(pos + glm::vec2(0, header), glm::vec2(pos.x + size.x, pos.y + header), 2, Color::White);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, Color::White);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, Color::White);

    sb.drawText(text, {pos.x + 5, pos.y}, WinS::f, Color::White);

    closeb->Draw();

    WContainer::Draw();
}

void Win::Update()
{
    glm::vec2 wpos = globalPos();
    if(!WinS::MouseHooked && inLimsV(Mouse::getCursorLastPos(), wpos, wpos + glm::vec2(size.x - 20, header)))
    {
        if(Mouse::isLeftPressed())
        {
            drag_point = Mouse::getCursorLastPos() - pos;
            dragged = true;
        }
    }
    if(Mouse::IsLeftDown() && dragged)
        pos = glm::vec2(Mouse::getCursorPos().x, Mouse::getCursorLastPos().y) - drag_point;
    else
        dragged = false;

    if(!WinS::MouseHooked && inLimsV(Mouse::getCursorLastPos(), wpos + glm::vec2(size.x - 10, size.y - 10), wpos + size))
    {
        Mouse::state = Mouse::STATE_RESIZE;
        if(Mouse::isLeftPressed())
        {
            resize_point = Mouse::getCursorLastPos() - size;
            resizing = true;
        }
    }
    if(Mouse::IsLeftDown() && resizing)
    {
        size = glm::vec2(Mouse::getCursorPos().x, Mouse::getCursorLastPos().y) - resize_point;
        if(size.y < 40)
            size.y = 40;
        if(size.x < 100)
            size.x = 100;
    }
    else
        resizing = false;

    WContainer::Update();

    if(!WinS::MouseHooked && inLimsV(Mouse::getCursorLastPos(), wpos, wpos + size))
    {
        if(Mouse::IsLeftDown())
        {
            WinS::ws->ToTop(this);
        }
        WinS::MouseHooked = true;
    }
}

void Win::MoveUnderCur()
{
    pos = Mouse::getCursorPos();
    if(pos.x + size.x > RESX)
    {
        pos.x = RESX - size.x;
    }
    if(pos.y + size.y > RESY)
    {
        pos.y = RESY - size.y;
    }
}
