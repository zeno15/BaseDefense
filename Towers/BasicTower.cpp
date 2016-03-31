#include <Towers/BasicTower.hpp>

#include <zeno/System/VectorMath.hpp>
#include <Application.hpp>
#include <Managers/ProjectileManager.hpp>
#include <Projectiles/BasicProjectile.hpp>
#include <Managers/TextureManager.hpp>

#include <iostream>

BasicTower::BasicTower(zeno::Texture& _texture, const zeno::Vector2f& _position) :
Tower(_texture, _position, 256.0f, (static_cast<float>(rand() % 500) + 1000.0f) / 1000.0f),
m_ElapsedCooldown(1.0f),
m_Cooldown(1.0f)
{

}
BasicTower::~BasicTower(void)
{

}


void BasicTower::update(float _delta)
{
    if (m_ElapsedCooldown < m_Cooldown) {
        m_ElapsedCooldown += _delta;
    }

    bool refindTarget = true;

    if (m_CurrentTarget != nullptr) {
        if (m_CurrentTarget->isAlive()) {
            if (isInRange(m_CurrentTarget)) {
                if (m_CurrentTarget->getUnreservedHealth() > 0) {
                    refindTarget = false;
                }
            }
        }
    }

    if (refindTarget) {
        m_CurrentTarget = getMostDangerousCreepInRange();
    }


    if (m_CurrentTarget != nullptr) {
        faceCurrentTarget();

        tryShoot();
    }
}

void BasicTower::tryShoot(void)
{
    if (m_ElapsedCooldown >= m_Cooldown) {
        m_ElapsedCooldown -= m_Cooldown;

        m_CurrentTarget->reserveDamage(m_Damage);

        sProjectileManager.addProjectile(new BasicProjectile(sTextureManager.getTexture(TextureManager::Texture::ProjectileBasic), *m_CurrentTarget, sprite.getPosition(), m_Damage));
    }
}