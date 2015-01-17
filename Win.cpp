#include "ui_win.h"
#include <glm/glm.hpp>
#include "ui_wins.h"
#include "mouse.h"
#include <vector>
#include "colorextender.h"
#include "jhelper.inl"

Win::Win(void) :
    size(100, 100),
    pos(0),
    col(0,0,0,0.75)
{
    //text = new TextGeometry("azazazaadasdasd");
}

Win::Win(glm::vec2 &p, glm::vec2 &s) :
    size(s),
    pos(p),
    col(0,0,0,0.75f)
{
    //text = new TextGeometry("azazazaadasdasd");
}

Win::Win(glm::vec2 &p, glm::vec2 &s, glm::vec4 &t_col) :
    size(s),
    pos(p),
    col(t_col)
{
    //text = new TextGeometry("azazazaadasdasd");
}


Win::~Win()
{
    if(Items.size() > 0){
        for(unsigned int i=0; i< Items.size(); i++){
            delete Items[i];
        }
    }
    Items.clear();
    //delete text;
}

void Win::Draw() const
{
    SpriteBatch& sb = *WinS::sb;

    sb.drawRect(pos, size, col);
    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WHITE);

    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WHITE);
    sb.drawLine(pos + glm::vec2(0,20), glm::vec2(pos.x + size.x, pos.y + 20), 2, WHITE);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WHITE);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WHITE);

    //text->DrawAt(atCenter(text->Size, pos, glm::vec2(size.x, 20)));

    if(Items.size() > 0){
        for(unsigned int i=0; i< Items.size(); i++){
            Items[i]->Draw();
        }
    }
}

void Win::Update()
{
    glm::vec2 wpos = GlobalPos();
    if(!WinS::MouseHooked && inLimsV(Mouse::GetCursorLastPos(), wpos, wpos + glm::vec2(size.x,20))){
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
        for(unsigned int i=0; i< Items.size(); i++){
            Items[i]->Update(); 
        }
    }

    if(!WinS::MouseHooked && inLimsV(Mouse::GetCursorLastPos(), wpos, wpos + size)){
        if(Mouse::IsLeftDown()){
            WinS::ToTop(this);
        }
        WinS::MouseHooked = true;
    }
}

glm::vec2 Win::GlobalPos() const
{
    return pos;
}
