#include <BaseObjects/Creep.hpp>

#include <BaseObjects/CreepPath.hpp>

#include <zeno/System/VectorMath.hpp>

#include <iostream>
#include <Managers/NotificationManager.hpp>

Creep::Creep(zeno::Texture& _texture, CreepPath& _creepPath, float _maxHealth) :
Entity(_texture),
m_HealthBar(_texture.getSize().x),
m_CreepPath(_creepPath),
m_Speed(128.0f),
m_CreepPathIndex(0),
m_Health(_maxHealth),
m_MaxHealth(_maxHealth),
m_ReservedHealthDamage(0.0f)
{
}

void Creep::update(float _delta)
{
    const Waypoint& waypoint = m_CreepPath.getWaypointAtIndex(m_CreepPathIndex);

    zeno::Vector2f difference = waypoint.position - sprite.getPosition();
    zeno::normalise(difference);

    zeno::Vector2f movement = difference * m_Speed * _delta;

    if (zeno::length(difference) >= 0.1f) {

        float angle = std::atan2(difference.y, difference.x);

        angle = (angle / 3.14159265f * 180.0f);

        if (angle > 90.0f)
        {
            angle = 450.0f - angle;
        }
        else
        {
            angle = 90.0f - angle;
        }

        angle = angle + 270.0f;

        angle = angle >= 360.0f ? angle - 360.0f : angle;

        sprite.setRotation(angle);
    }

    if (zeno::length(waypoint.position - sprite.getPosition()) > m_Speed * _delta)
    {
        sprite.setPosition(sprite.getPosition() + movement);
        m_HealthBar.setPosition(sprite.getPosition());
        return;
    }

    sprite.setPosition(waypoint.position);
    m_HealthBar.setPosition(sprite.getPosition());

    if (waypoint.type == Waypoint::WaypointType::End) {
        sNotification.onCreepReachedEnd(*this, m_CreepPath);
        m_Alive = false;
        return;
    }


    m_CreepPathIndex += 1;
}

void Creep::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection) {
    sprite.render(_view, _projection);
    if (m_Health != m_MaxHealth) {
        m_HealthBar.render(_view, _projection);
    }
}

float Creep::getSpeed(void) const
{
    return m_Speed;
}
void Creep::setSpeed(float _speed)
{
    m_Speed = _speed;
}

unsigned int Creep::getPathIndex(void) const
{
    return m_CreepPathIndex;
}
float Creep::getDistanceToWaypoint(void) const
{
    return zeno::distance(m_CreepPath.getWaypointAtIndex(m_CreepPathIndex).position, sprite.getPosition());
}

void Creep::damage(float _amount)
{
    m_Health -= _amount;

    if (m_Health > m_MaxHealth) {
        m_Health = m_MaxHealth;
    }

    if (m_Health <= 0) {
        sNotification.onCreepDied(*this);
        kill();
    }

    m_HealthBar.setFraction(m_Health / m_MaxHealth);
}
void Creep::applyReservedDamage(float _amount)
{
    if (_amount <= 0.0f) {
        return;
    }

    m_ReservedHealthDamage -= _amount;

    damage(_amount);
}
void Creep::reserveDamage(float _amount)
{
    if (_amount <= 0.0f) {
        return;
    }

    m_ReservedHealthDamage += _amount;
}

float Creep::getUnreservedHealth(void) const
{
    return m_Health - m_ReservedHealthDamage;
}