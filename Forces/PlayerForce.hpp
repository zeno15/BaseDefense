#ifndef BASEDEFENSE_PLAYERFORCE_HPP
#define BASEDEFENSE_PLAYERFORCE_HPP

#include <BaseObjects/Force.hpp>

#include <zeno/System/Mat4x4.hpp>
#include <zeno/Graphics/Rectangle.hpp>
#include <Managers/TowerManager.hpp>

class PlayerForce : public Force {
public:
    PlayerForce(unsigned int _maxHealth);

    void update(float _delta);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    void removeHealth(unsigned int _damage);
    unsigned int getHealth(void) const;

    bool isAlive(void) const;

    void createTower(const std::string& _towerName, const zeno::Vector2f& _position);

private:
    unsigned int m_Health;
    unsigned int m_MaxHealth;

    zeno::Rectangle m_HealthIndicator;
    zeno::Rectangle m_HealthIndicatorBackground;
};


#endif //BASEDEFENSE_PLAYERFORCE_HPP
