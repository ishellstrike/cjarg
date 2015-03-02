#include "label.h"
#include "wins.h"
#include "sge/colorextender.h"

Label::Label(WContainer *par) :
    WComponent(par)
{
    size = {20,20};
    text("empty");
}

Label::~Label()
{

}

void Label::text(const std::string &__s)
{
    m_text = __s;
    size = WinS::sb->measureText(m_text, WinS::f);
}

const std::string Label::text() const
{
    return m_text;
}

void Label::append(const std::string &__s)
{
    m_text.append(__s);
    size = WinS::sb->measureText(m_text, WinS::f);
}

void Label::Draw() const
{
    glm::vec2 p = globalPos();
    WinS::sb->drawText(m_text, p, size, WinS::f, aimed ? WinS::color.hovered_text : WinS::color.text,
                       SpriteBatch::ALIGN_LEFT);

    WComponent::Draw();
}

void Label::Update()
{
    WComponent::Update();
}
