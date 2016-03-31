#ifndef BASEDEFENSE_SPRITE_HPP
#define BASEDEFENSE_SPRITE_HPP

#include <zeno/Graphics/Colour.hpp>
#include <zeno/Graphics/Texture.hpp>
#include <zeno/System/Mat4x4.hpp>

class Sprite
{
public:
    Sprite(zeno::Texture& _texture);
    ~Sprite(void);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    float getRotation(void) const;
    void setRotation(float _rotation);

    zeno::Colour getColour(void) const;
    void setColour(zeno::Colour _colour);

    zeno::Vector2f getPosition(void) const;
    void setPosition(const zeno::Vector2f& _position);

    zeno::Vector2f getScale(void) const;
    void setScale(const zeno::Vector2f& _scale);

    zeno::Vector2f getOrigin(void) const;
    void setOrigin(const zeno::Vector2f& _origin);

    zeno::Vector2f getSize(void) const;

private:
    unsigned int m_VAO;
    unsigned int m_VBOPosition;
    unsigned int m_VBOTexture;

    float m_Rotation;

    zeno::Colour m_Colour;

    zeno::Texture& m_Texture;

    zeno::Vector2f m_Position;
    zeno::Vector2f m_Origin;
    zeno::Vector2f m_Scale;
    zeno::Vector2f m_Size;
};


#endif //BASEDEFENSE_SPRITE_HPP
