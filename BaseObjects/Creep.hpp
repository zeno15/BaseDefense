#ifndef BASEDEFENSE_CREEP_HPP
#define BASEDEFENSE_CREEP_HPP

#include <BaseObjects/Entity.hpp>
#include <Waypoint.hpp>
#include <MiscellaneousRenderables/HealthBar.hpp>

class CreepPath;

class Creep : public Entity
{
public:
    Creep(zeno::Texture& _texture, CreepPath& _creepPath, float _maxHealth);

    virtual void update(float _delta);

    virtual void render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection);

    float getSpeed(void) const;
    void setSpeed(float _speed);

    unsigned int getPathIndex(void) const;
    float getDistanceToWaypoint(void) const;

    void damage(float _amount);
    void applyReservedDamage(float _amount);
    void reserveDamage(float _amount);

    float getUnreservedHealth(void) const;

private:
    CreepPath& m_CreepPath;

    HealthBar m_HealthBar;

    unsigned int m_CreepPathIndex;

    float m_Speed;

    float m_Health;
    float m_MaxHealth;
    float m_ReservedHealthDamage;
};


#endif //BASEDEFENSE_CREEP_HPP
