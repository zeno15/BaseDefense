#include <Projectiles/BasicProjectile.hpp>

#include <iostream>

BasicProjectile::BasicProjectile(zeno::Texture& _texture, Creep& _creep, const zeno::Vector2f& _position, float _damage) :
Projectile(_texture, _creep, 1024.0f, _damage)
{
    sprite.setPosition(_position);
}

void BasicProjectile::onCollideWithTarget(void)
{
    m_Target->applyReservedDamage(m_Damage);

    kill();
}