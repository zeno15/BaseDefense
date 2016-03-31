#ifndef BASEDEFENSE_HEALTHBAR_HPP
#define BASEDEFENSE_HEALTHBAR_HPP


#include <zeno/System/Mat4x4.hpp>
#include <zeno/System/Vector2.hpp>
#include <zeno/Graphics/Colour.hpp>

class HealthBar
{
public:
    HealthBar(float _size);
    ~HealthBar(void);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    void setPosition(const zeno::Vector2f& _position);

    void setFraction(float _fraction);

private:
    float m_Fraction;
    float m_Size;

    zeno::Colour m_Colour;

    zeno::Vector2f m_Position;

    unsigned int m_VAO;
    unsigned int m_PositionVBO;
    unsigned int m_ColourVBO;
};


#endif //BASEDEFENSE_HEALTHBAR_HPP
