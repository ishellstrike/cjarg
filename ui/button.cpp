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

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, aimed ? aimed_color : color);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, aimed ? aimed_color : color);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, aimed ? aimed_color : color);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, aimed ? aimed_color : color);

    WinS::sb->drawText(text, pos, size, WinS::f, aimed ? aimed_color : color, SpriteBatch::ALIGN_CENTER);

    WComponent::Draw();
}

void Button::Update()
{
    WComponent::Update();
}

