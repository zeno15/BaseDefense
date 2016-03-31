#include <BaseObjects/Projectile.hpp>

#include <zeno/System/VectorMath.hpp>

#include <iostream>

Projectile::Projectile(zeno::Texture& _texture, Creep& _creep, float _speed, float _damage) :
sprite(_texture),
m_Target(&_creep),
m_IsAlive(true),
m_Speed(_speed),
m_Damage(_damage),
m_PreviousTargetPosition(_creep.getPosition())
{

}


void Projectile::update(float _delta)
{

    zeno::Vector2f targetPosition = m_PreviousTargetPosition;
    if (m_Target->isAlive()){
        targetPosition = m_Target->getPosition();
        m_PreviousTargetPosition = targetPosition;
    }

    zeno::Vector2f difference = targetPosition - sprite.getPosition();
    zeno::normalise(difference);

    zeno::Vector2f movement = difference * m_Speed * _delta;

    if (zeno::length(difference) >= 0.1f) {

        float angle = std::atan2(-difference.y, difference.x);

        angle  = angle * 180.0f / 3.14159265f;

        if (angle < 0.0f) {
            angle += 360.0f;
        }

        sprite.setRotation(angle);
    }

    if (zeno::length(targetPosition - sprite.getPosition()) > m_Speed * _delta)
    {
        sprite.setPosition(sprite.getPosition() + movement);
        return;
    }

    sprite.setPosition(targetPosition);


    onCollideWithTarget();
}

void Projectile::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    sprite.render(_view, _projection);
}

void Projectile::kill(void)
{
    m_IsAlive = false;
}

bool Projectile::isAlive(void) const
{
    return m_IsAlive;
}