#ifndef SCHEME_H
#define SCHEME_H
#include "logic/agents/agent.h"
#include <vector>
#include <glm/glm.hpp>
#include <sge/logger.h>
#include <map>

typedef std::string SchemeType;
typedef char Letter;

struct Scheme
{
    enum TRANSFORM {
        TRANSFORM_MX,
        TRANSFORM_MY,
        TRANSFORM_RCW,
        TRANSFORM_AFTER_LAST
    };

    std::vector<std::vector<Letter>> data;
    std::map<Letter, std::string> dict;

    /*!
     * \brief Отражение схемы по горизонтали
     */
    void MirrorX();

    /*!
     * \brief Отражение схемы по вертикали
     */
    void MirrorY();

    /*!
     * \brief Поворот схемы по чесовой стрелке
     */
    void RotateCCW();

    /*!
     * \brief Транспонирование схемы
     */
    void Transpose();

    void Resize(glm::vec2 __size);
    void LogData() const;
    glm::vec2 size;
    SchemeType type;

    void Set(std::vector<std::vector<Letter>> __data);

    /*!
     * \brief Производит изменение № = остаток от деления __num на число возможных трансформаций
     * \param __num
     *
     * \code for(int i = 0; i < 5; ++i) NumericTransform(rnd()); //4 случайных трансформации
     * \code NumericTransform(Scheme::TRANSFORM_RCW);
     */
    void NumericTransform(int __num);
};

#endif // SCHEME_H
