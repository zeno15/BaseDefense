#ifndef BASEDEFENSE_BASICPROJECTILE_HPP
#define BASEDEFENSE_BASICPROJECTILE_HPP

#include <BaseObjects/Projectile.hpp>

class BasicProjectile : public Projectile
{
public:
    BasicProjectile(zeno::Texture& _texture, Creep& _creep, const zeno::Vector2f& _position, float _damage);

    virtual void onCollideWithTarget(void);

private:


};


#endif //BASEDEFENSE_BASICPROJECTILE_HPP
