#include "ui/win.h"
#include <glm/glm.hpp>
#include "ui/wins.h"
#include "sge/mouse.h"
#include <vector>
#include "sge/colorextender.h"
#include "sge/helper.h"

Win::Win(void) :
    size(100, 100),
    pos(0),
    col(0,0,0,0.75)
{
    text = std::unique_ptr<TextGeometry>(new TextGeometry(WinS::sb, WinS::f));
    text->setString("asdasdasd");
}

Win::Win(glm::vec2 &p, glm::vec2 &s) :
    size(s),
    pos(p),
    col(0,0,0,0.75f)
{
    text = std::unique_ptr<TextGeometry>(new TextGeometry(WinS::sb, WinS::f));
    text->setString("asdasdasd");
}

Win::Win(glm::vec2 &p, glm::vec2 &s, glm::vec4 &t_col) :
    size(s),
    pos(p),
    col(t_col)
{
    text = std::unique_ptr<TextGeometry>(new TextGeometry(WinS::sb, WinS::f));
    text->setString("asdasdasd");
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
    sb.drawLine(pos + glm::vec2(0, 20), glm::vec2(pos.x + size.x, pos.y + 20), 2, Color::White);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, Color::White);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, Color::White);

    text->Draw({pos.x + 5, pos.y});

    if(Items.size() > 0)
    {
        for(unsigned int i = 0; i< Items.size(); ++i)
        {
            Items[i]->Draw();
        }
    }
}

void Win::Update()
{
    glm::vec2 wpos = GlobalPos();
    if(!WinS::MouseHooked && inLimsV(Mouse::GetCursorLastPos(), wpos, wpos + glm::vec2(size.x, 20)))
    {
        if(Mouse::IsLeftPressed())
        {
            drag_point = Mouse::GetCursorLastPos() - pos;
            dragged = true;
        }
    }
    if(Mouse::IsLeftDown() && dragged)
        pos = glm::vec2(Mouse::GetCursorPos().x, Mouse::GetCursorLastPos().y) - drag_point;
    else
        dragged = false;

    if(Items.size() > 0){
        for(unsigned int i=0; i< Items.size(); ++i)
        {
            Items[i]->Update(); 
        }
    }

    if(!WinS::MouseHooked && inLimsV(Mouse::GetCursorLastPos(), wpos, wpos + size))
    {
        if(Mouse::IsLeftDown())
        {
            WinS::ToTop(this);
        }
        WinS::MouseHooked = true;
    }
}

glm::vec2 Win::GlobalPos() const
{
    return pos;
}
