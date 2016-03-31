#include <Forces/PlayerForce.hpp>
#include <Application.hpp>

#define HEALTH_HEIGHT 20.0f
#define HEALTH_WIDTH 200.0f

PlayerForce::PlayerForce(unsigned int _maxHealth) :
m_MaxHealth(_maxHealth),
m_Health(_maxHealth),
m_HealthIndicator(zeno::Vector2f(HEALTH_WIDTH, HEALTH_HEIGHT), zeno::Vector2f(0.0f, sApp.m_Window.getSize().y - HEALTH_HEIGHT)),
m_HealthIndicatorBackground(zeno::Vector2f(HEALTH_WIDTH, HEALTH_HEIGHT), zeno::Vector2f(0.0f, sApp.m_Window.getSize().y - HEALTH_HEIGHT))
{
    m_HealthIndicator.setInternalColour(zeno::Colour::Green);
}

void PlayerForce::update(float _delta)
{

}

void PlayerForce::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    m_HealthIndicator.render(_projection * _view);
    m_HealthIndicatorBackground.render(_projection * _view);
}

void PlayerForce::removeHealth(unsigned int _damage)
{
    if (m_Health < _damage) {
        m_Health = 0;
    }
    else {
        m_Health -= _damage;
    }

    m_HealthIndicator.setSize(zeno::Vector2f(static_cast<float>(m_Health) / static_cast<float>(m_MaxHealth) * HEALTH_WIDTH, HEALTH_HEIGHT));
}
unsigned int PlayerForce::getHealth(void) const
{
    return m_Health;
}

bool PlayerForce::isAlive(void) const
{
    return m_Health > 0;
}
void PlayerForce::createTower(const std::string& _towerName, const zeno::Vector2f& _position)
{
    if (sTowerManager.createTower("BasicTower", _position))
    {

    }
    else {
        std::cout << "Could not create tower" << std::endl;
    }
}