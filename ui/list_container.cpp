#include "list_container.h"
#include "wins.h"
#include "sge/colorextender.h"
#include "label.h"

void ListContainer::nolmalze_top_bot()
{
    top = glm::max(0, glm::min(top, (int)Items.size() - stored_items_offset));
}

ListContainer::ListContainer(WContainer *par) :
    WContainer(par)
{
    for(int i=0;i<10;i++)
    {
        auto l = new Label(this);
        l->text("test"+std::to_string(i));
        l->aimed_color = Color::Yellow;
    }

    size = {150,50};

    up = new Button(this);
    up->text = "^";
    up->anchor = ANCHOR_TOP_RIGHT;
    up->size = {20,20};
    up->pos = {-20,0};
    up->onLeftPress = [&](){
        top--;
        nolmalze_top_bot();
    };

    down = new Button(this);
    down->text = "v";
    down->anchor = ANCHOR_DOWN_RIGHT;
    down->size = {20,20};
    down->pos = {-20,-20};
    down->onLeftPress = [&](){
        top++;
        nolmalze_top_bot();
    };

    bar = new VerticalBar(this);
    up->text = "^";
    bar->anchor = ANCHOR_TOP_RIGHT;
    bar->pos = {-20, 20};
    bar->size = {20, 20};
    bar->onLeftPress = [&](){
        top--;
        nolmalze_top_bot();
    };

    onWheelDown = [&](){
        top++;
        nolmalze_top_bot();
    };

    onWheelUp = [&](){
        top--;
        nolmalze_top_bot();
    };
}

ListContainer::~ListContainer()
{

}

void ListContainer::Draw() const
{
    SpriteBatch &sb = *WinS::sb;
    auto pos = globalPos();

    for(auto i = Items.begin(); i != Items.end() - stored_items_offset; ++i)
    {
        (*i)->hidden = true;
    }
    int j = 0;
    bar->top = top/(float)(Items.size() - stored_items_offset);
    for(auto i = Items.begin() + top; i != Items.end() - stored_items_offset; ++i, ++j)
    {
        if((j)*20 >= size.y)
        {
            bar->bot = (top+j+1)/(float)(Items.size() - stored_items_offset);
            break;
        }
        (*i)->hidden = false;
        (*i)->pos = glm::vec2(0, j * 20);
    }

    sb.drawLine(pos, glm::vec2(pos.x, pos.y + size.y), 2, WinS::color.border_up);
    sb.drawLine(pos, glm::vec2(pos.x + size.x, pos.y), 2, WinS::color.border_up);
    sb.drawLine(glm::vec2(pos.x, pos.y + size.y), pos + size, 2, WinS::color.border_down);
    sb.drawLine(glm::vec2(pos.x + size.x, pos.y), pos + size, 2, WinS::color.border_down);

    WContainer::Draw();
}

void ListContainer::Update()
{
    bar->size.y = size.y - 40;
    WContainer::Update();
}
