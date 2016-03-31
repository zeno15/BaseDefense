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

    template <typename T>
    void addTower(TextureManager::Texture _texture, const zeno::Vector2i& _tilecoordinates) {
        if (sTowerManager.addTower<T>(_texture, _tilecoordinates))
        {
            std::cout << "Tower placed, costing yoooo!" << std::endl;
        }
        else {
            std::cout << "Could not place tower, not charged." << std::endl;
        }
    }

private:
    unsigned int m_Health;
    unsigned int m_MaxHealth;

    zeno::Rectangle m_HealthIndicator;
    zeno::Rectangle m_HealthIndicatorBackground;
};


#endif //BASEDEFENSE_PLAYERFORCE_HPP
