#ifndef BASEDEFENSE_BASICTOWER_HPP
#define BASEDEFENSE_BASICTOWER_HPP

#include <BaseObjects/Tower.hpp>

class BasicTower : public Tower
{
public:
    BasicTower(zeno::Texture& _texture, const zeno::Vector2f& _position);
    ~BasicTower(void);

    virtual void update(float _delta);

private:
    void tryShoot(void);

private:
    float m_ElapsedCooldown;
    float m_Cooldown;
};


#endif //BASEDEFENSE_BASICTOWER_HPP
