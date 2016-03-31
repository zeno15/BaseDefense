#include <BaseObjects/Sprite.hpp>

#include <GL/glew.h>
#include <zeno/Graphics/ShaderManager.hpp>

#include <iostream>

#define NUM_VERTEXES 6

Sprite::Sprite(zeno::Texture& _texture) :
m_Texture(_texture),
m_Size(_texture.getSize()),
m_Scale(1.0f, 1.0f),
m_Colour(zeno::Colour::White),
m_Rotation(0.0f)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //~ Positions
    glGenBuffers(1, &m_VBOPosition);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * 3, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    std::vector<float> positions = {
        - m_Size.x / 2.0f, - m_Size.y / 2.0f, 0.0f,
        + m_Size.x / 2.0f, - m_Size.y / 2.0f, 0.0f,
        + m_Size.x / 2.0f, + m_Size.y / 2.0f, 0.0f,

        - m_Size.x / 2.0f, - m_Size.y / 2.0f, 0.0f,
        + m_Size.x / 2.0f, + m_Size.y / 2.0f, 0.0f,
        - m_Size.x / 2.0f, + m_Size.y / 2.0f, 0.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * positions.size(), positions.data());



    //~ Textures
    glGenBuffers(1, &m_VBOPosition);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBOPosition);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * 2, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    std::vector<float> textures = {
        0.0f, 0.0f,
        1.0f, 0.0f,
        1.0f, 1.0f,

        0.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * textures.size(), textures.data());
}
Sprite::~Sprite(void)
{
    glDeleteBuffers(1, &m_VBOPosition);
    glDeleteBuffers(1, &m_VBOTexture);

    glDeleteVertexArrays(1, &m_VAO);
}


void Sprite::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    glBindVertexArray(m_VAO);

    zeno::ShaderManager::getInstance().getShader("Sprite").bind();

    m_Texture.bind();

    zeno::Mat4x4 model = zeno::Mat4x4::createTranslation(zeno::Vector3f(m_Position.x, m_Position.y, 0.0f));
    model *= zeno::Mat4x4::createRotationZ(m_Rotation * 3.14159265f / 180.0f);
    model *= zeno::Mat4x4::createScale(zeno::Vector3f(m_Scale.x, m_Scale.y, 0.0f));
    model *= zeno::Mat4x4::createTranslation(zeno::Vector3f(-m_Origin.x, -m_Origin.y, 0.0f));

    zeno::ShaderManager::getInstance().getShader("Sprite").passUniform("projection", _projection);
    zeno::ShaderManager::getInstance().getShader("Sprite").passUniform("model", model);
    zeno::ShaderManager::getInstance().getShader("Sprite").passUniform("view", _view);
    zeno::ShaderManager::getInstance().getShader("Sprite").passUniform("colour", m_Colour);

    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES);

    m_Texture.unbind();

    zeno::ShaderManager::getInstance().getShader("Sprite").unbind();

    glBindVertexArray(0);
}

float Sprite::getRotation(void) const
{
    return m_Rotation;
}
void Sprite::setRotation(float _rotation)
{
    m_Rotation = _rotation;
}

zeno::Colour Sprite::getColour(void) const
{
    return m_Colour;
}
void Sprite::setColour(zeno::Colour _colour)
{
    m_Colour = _colour;
}

zeno::Vector2f Sprite::getPosition(void) const
{
    return m_Position;
}
void Sprite::setPosition(const zeno::Vector2f& _position)
{
    m_Position = _position;
}

zeno::Vector2f Sprite::getScale(void) const
{
    return m_Scale;
}
void Sprite::setScale(const zeno::Vector2f& _scale)
{
    m_Scale = _scale;
}

zeno::Vector2f Sprite::getOrigin(void) const
{
    return m_Origin;
}
void Sprite::setOrigin(const zeno::Vector2f& _origin)
{
    m_Origin = _origin;
}

zeno::Vector2f Sprite::getSize(void) const
{
    return m_Size;
}