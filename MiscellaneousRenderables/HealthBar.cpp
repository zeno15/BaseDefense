#include <MiscellaneousRenderables/HealthBar.hpp>

#include <GL/glew.h>
#include <zeno/Graphics/ShaderManager.hpp>

#define NUM_VERTEXES 6

#define HEIGHT 8.0f

HealthBar::HealthBar(float _size) :
m_Size(_size)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //~ Positions
    glGenBuffers(1, &m_PositionVBO);

    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NUM_VERTEXES * 3, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    setFraction(1.0f);
}
HealthBar::~HealthBar(void)
{
    glDeleteBuffers(1, &m_PositionVBO);
    glDeleteVertexArrays(1, &m_VAO);
}


void HealthBar::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    glBindVertexArray(m_VAO);

    zeno::ShaderManager::getInstance().getShader("HealthBar").bind();

    zeno::Mat4x4 model = zeno::Mat4x4::createTranslation(zeno::Vector3f(m_Position.x, m_Position.y + m_Size, 0.1f));

    zeno::ShaderManager::getInstance().getShader("HealthBar").passUniform("projection", _projection);
    zeno::ShaderManager::getInstance().getShader("HealthBar").passUniform("model", model);
    zeno::ShaderManager::getInstance().getShader("HealthBar").passUniform("view", _view);
    zeno::ShaderManager::getInstance().getShader("HealthBar").passUniform("barColour", m_Colour);

    glDrawArrays(GL_TRIANGLES, 0, NUM_VERTEXES);

    zeno::ShaderManager::getInstance().getShader("HealthBar").unbind();

    glBindVertexArray(0);
}
void HealthBar::setPosition(const zeno::Vector2f& _position)
{
    m_Position = _position;
}

void HealthBar::setFraction(float _fraction)
{
    if (_fraction == m_Fraction) {
        return;
    }
    if (_fraction <= 0.0f) {
        _fraction = 0.0f;
    }
    m_Fraction = _fraction;

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    std::vector<float> positions = {
            - m_Size / 2.0f, - HEIGHT / 2.0f, 0.0f,
            - m_Size / 2.0f + m_Fraction * m_Size, - HEIGHT / 2.0f, 0.0f,
            - m_Size / 2.0f + m_Fraction * m_Size, + HEIGHT / 2.0f, 0.0f,

            - m_Size / 2.0f, - HEIGHT / 2.0f, 0.0f,
            - m_Size / 2.0f + m_Fraction * m_Size, + HEIGHT / 2.0f, 0.0f,
            - m_Size / 2.0f, + HEIGHT / 2.0f, 0.0f
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * positions.size(), positions.data());

    if (m_Fraction > 0.75f) {
        m_Colour = zeno::Colour::Green;
    } else if (m_Fraction > 0.25f) {
        m_Colour = zeno::Colour::Yellow;
    } else {
        m_Colour = zeno::Colour::Red;
    }
}