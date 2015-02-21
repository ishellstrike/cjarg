#include "button.h"
#include "wins.h"
#include "sge/colorextender.h"
#include "sge/mouse.h"
#include "sge/helper.h"

Button::Button(WContainer *par) :
    WComponent(par)
{
}

Button::~Button()
{

}

void Button::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = GlobalPos();

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, aimed ? Color::White : Color::LightGrey);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, aimed ? Color::White : Color::LightGrey);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, aimed ? Color::White : Color::LightGrey);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, aimed ? Color::White : Color::LightGrey);

    WinS::sb->drawText(text, pos, size, WinS::f, aimed ? Color::White : Color::LightGrey, SpriteBatch::ALIGN_CENTER);
}

void Button::Update()
{

}

