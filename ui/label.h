#ifndef LABEL_H
#define LABEL_H
#include "component.h"
#include <glm/glm.hpp>

class Label : public WComponent
{
public:
    Label(WContainer *par);
    ~Label();

    void text(const std::string &__s);
    const std::string text() const;
    void append(const std::string &__s);

    void Draw() const;
    void Update();
private:
    std::string m_text;
};

#endif // LABEL_H
