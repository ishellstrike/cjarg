#include "button.h"
#include "wins.h"
#include "sge/colorextender.h"
#include "sge/mouse.h"
#include "sge/helper.h"

Button::Button(WContainer *par) :
    WComponent(par)
{
    color = Color::LightGrey;
}

Button::~Button()
{

}

void Button::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    bool pressed = false;
    if(aimed && Mouse::IsLeftDown())
        pressed = true;

    glm::vec4 border_up = pressed ? WinS::color.border_down : WinS::color.border_up;
    glm::vec4 border_down = pressed ? WinS::color.border_up : WinS::color.border_down;

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, border_down);

    WinS::sb->drawText(text, pos, size, WinS::f, aimed ? WinS::color.text : WinS::color.hovered_text, SpriteBatch::ALIGN_CENTER);

    WComponent::Draw();
}

void Button::Update()
{
    WComponent::Update();
}

