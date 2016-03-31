#include <Managers/ProjectileManager.hpp>

#include <iostream>

ProjectileManager::ProjectileManager(void)
{

}

ProjectileManager::~ProjectileManager(void)
{

}


void ProjectileManager::update(float _delta)
{
    for (unsigned int i = 0; i < m_Projectiles.size(); i += 1) {
        m_Projectiles.at(i)->update(_delta);

        if (!m_Projectiles.at(i)->isAlive()) {
            delete m_Projectiles.at(i);

            m_Projectiles.erase(m_Projectiles.begin() + i);
        }
    }
}

void ProjectileManager::render(const zeno::Mat4x4& _view, const zeno::Mat4x4& _projection)
{
    for (unsigned int i = 0; i < m_Projectiles.size(); i += 1) {
        m_Projectiles.at(i)->render(_view, _projection);
    }
}

void ProjectileManager::addProjectile(Projectile *_projectile)
{
    m_Projectiles.push_back(_projectile);
}