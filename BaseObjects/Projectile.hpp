#ifndef BASEDEFENSE_PROJECTILE_HPP
#define BASEDEFENSE_PROJECTILE_HPP

#include <BaseObjects/Sprite.hpp>
#include <BaseObjects/Creep.hpp>

class Projectile
{
public:
    Projectile(zeno::Texture& _texture, Creep& _creep, float _speed, float _damage);

    virtual void onCollideWithTarget(void) = 0;

    void update(float _delta);

    void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    void kill(void);

    bool isAlive(void) const;

protected:
    Sprite sprite;

    Creep *m_Target;

    bool m_IsAlive;

    float m_Speed;

    float m_Damage;

    zeno::Vector2f m_PreviousTargetPosition;
};


#endif //BASEDEFENSE_PROJECTILE_HPP
